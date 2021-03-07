#pragma once

class IMaterialVar
{
public:
	void* getTexture() {
		using original_fn = void* (__thiscall*)(IMaterialVar*);
		return (*(original_fn**)this)[1](this);
	}

	void setFloat(float val) {
		using original_fn = void(__thiscall*)(IMaterialVar*, float);
		return (*(original_fn**)this)[4](this, val);
	}

	void setInt(int val) {
		using original_fn = void(__thiscall*)(IMaterialVar*, int);
		return (*(original_fn**)this)[5](this, val);
	}

	void setString(char const* val) {
		using original_fn = void(__thiscall*)(IMaterialVar*, char const*);
		return (*(original_fn**)this)[6](this, val);
	}

	void setColor(float r, float g, float b) {
		using original_fn = void(__thiscall*)(IMaterialVar*, float, float, float);
		return (*(original_fn**)this)[11](this, r, g, b);
	}

	void setTexture(void* val) {
		using original_fn = void(__thiscall*)(IMaterialVar*, void*);
		return (*(original_fn**)this)[15](this, val);
	}
};
