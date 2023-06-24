
#pragma once

class Beetle
{
public:
	Beetle();
	~Beetle();

	Beetle(const Beetle& _Other) = delete;
	Beetle(Beetle&& _Other) noexcept = delete;
	Beetle& operator=(const Beetle& _Other) = delete;
	Beetle& operator=(const Beetle&& _Other) noexcept = delete;


protected:

private:

};

