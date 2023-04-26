
#pragma once

class player
{
public:
	player();
	~player();

	player(const player& _Other) = delete;
	player(player&& _Other) noexcept = delete;
	player& operator=(const player& _Other) = delete;
	player& operator=(const player&& _Other) noexcept = delete;


protected:

private:

};

