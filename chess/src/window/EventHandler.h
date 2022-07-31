#pragma once
#include <SDL2/SDL.h>
#include "../Common.h"

class Application;
class Asset;
class Square;


class CHESS_API EventHandler
{
public:
	explicit EventHandler(Application& app) : app_(app) {}
	EventHandler(const EventHandler&) = delete;
	EventHandler(EventHandler&&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;
	EventHandler& operator=(EventHandler&&) = delete;
	virtual void operator()(const SDL_Event& e) = 0;
	virtual ~EventHandler() = default;
protected:
	Application& app_;
};

class CHESS_API QuitHandler final: public EventHandler
{
public:
	explicit QuitHandler(Application& app,bool& quit): EventHandler(app), quit_(quit){}
	void operator()(const SDL_Event&) noexcept override { this->quit_ = true; }
private:
	bool& quit_;
};

class CHESS_API MouseButtonHandler final: public EventHandler
{
public:
	explicit MouseButtonHandler(Application& app): EventHandler(app) {}
	void operator()(const SDL_Event&) noexcept override;
private:
	Square* get_square_of_coordinates(int x, int y) const noexcept;
	void move_asset(const Asset&, int x, int y) const noexcept;
};
