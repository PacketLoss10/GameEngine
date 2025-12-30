#include <SFML/Graphics.hpp>
#include <vector>
#include "InputHandler.h"

struct Light {
    sf::Vector2f position;
    float radius;
    sf::Color color;
    float intensity; // 0.0 = off, 1.0 = full strength
};

int main() {
    sf::RenderWindow window(sf::VideoMode({ 800,600 }), "SFML 3 Engine Lighting");
    window.setFramerateLimit(60);

    // Example sprite
    sf::Texture tex;
    tex.loadFromFile("sprite.png");
    sf::Sprite sprite(tex);
    sprite.setPosition(sf::Vector2f(400.f, 300.f));

    // Lights
    std::vector<Light> lights = {
        {{400,300}, 500.f, sf::Color::White, 0.5f},
        {{200,200}, 100.f, sf::Color(255,200,200), 0.6f}
    };

    sf::RectangleShape screenQuad({ 800.f,600.f });
    sf::RenderTexture lightTexture({ 800,600 });

    // Shader with intensity support
    const std::string fragShader = R"(
        uniform vec2 lightPos[10];
        uniform vec3 lightColor[10];
        uniform float lightRadius[10];
        uniform float lightIntensity[10];
        uniform int lightCount;
        uniform sampler2D sceneTexture;
        uniform vec2 resolution;

        void main() {
            vec2 uv = gl_FragCoord.xy / resolution;
            vec3 sceneCol = texture(sceneTexture, uv).rgb;

            // HDR-style light accumulation
            vec3 totalLight = vec3(0.0);
            for(int i=0;i<lightCount;i++){
                vec2 lp = lightPos[i] / resolution;
                float dist = distance(uv, lp);
                float falloff = clamp(1.0 - dist * resolution.x / lightRadius[i], 0.0, 1.0);
                totalLight += lightColor[i] * falloff * lightIntensity[i];
            }

            // Tone mapping to simulate real-world saturation
            vec3 finalCol = sceneCol + totalLight;       // additive light
            finalCol = finalCol / (finalCol + vec3(1.0)); // simple Reinhard tone mapping

            gl_FragColor = vec4(finalCol, 1.0);
        }
    )";

    sf::Shader shader;
    if (!shader.loadFromMemory(fragShader, sf::Shader::Type::Fragment)) return -1;

    while (window.isOpen()) {
        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        // Update first light to mouse
        sf::Vector2i mp = sf::Mouse::getPosition(window);
        lights[0].position = { (float)mp.x,(float)mp.y };

        // Pass lights to shader
        int maxLights = 10;
        int count = (int)lights.size();
        shader.setUniform("lightCount", count);
        shader.setUniform("resolution", sf::Glsl::Vec2(800.f, 600.f));

        for (int i = 0; i < count; i++) {
            shader.setUniform("lightPos[" + std::to_string(i) + "]", sf::Glsl::Vec2(lights[i].position));
            shader.setUniform("lightColor[" + std::to_string(i) + "]",
                sf::Glsl::Vec3(lights[i].color.r / 255.f, lights[i].color.g / 255.f, lights[i].color.b / 255.f));
            shader.setUniform("lightRadius[" + std::to_string(i) + "]", lights[i].radius);
            shader.setUniform("lightIntensity[" + std::to_string(i) + "]", lights[i].intensity);
        }

        // Draw scene
        window.clear(sf::Color::Black);
        window.draw(sprite);

        if (INPUT.is_key_held(sf::Keyboard::Key::A))
            lights[0].intensity -= 0.1f;
		if (INPUT.is_key_held(sf::Keyboard::Key::D))
			lights[0].intensity += 0.1f;

        // Draw lighting
        lightTexture.clear(sf::Color::Black);
        lightTexture.draw(screenQuad, &shader);
        lightTexture.display();

        sf::Sprite lightSprite(lightTexture.getTexture());
        window.draw(lightSprite, sf::BlendMultiply);

        window.display();
    }
}
