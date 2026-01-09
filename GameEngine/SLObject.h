#pragma once

#include "JSONOBJECT.h"

#define TO_JSON(...) \
    operator JSONOBJECT() const override \
    { \
        JSONOBJECT json; \
        __VA_ARGS__; \
        return json; \
    };

#define FROM_JSON(...) \
    void operator=(const JSONOBJECT& json) override \
    { \
        __VA_ARGS__; \
    };

class SLObject
{
protected:
public:
	virtual ~SLObject() = default;
	virtual operator JSONOBJECT() const = 0;
	virtual void operator=(const JSONOBJECT& json) = 0;
};