#pragma once
#include "BoardGame.h"

class EventHandler
{
public:
	explicit EventHandler(BoardGame& board) : board_(board){}
	EventHandler(const EventHandler&) = delete;
	EventHandler(EventHandler&&) = delete;
	EventHandler& operator=(const EventHandler&) = delete;
	EventHandler& operator=(EventHandler&&) = delete;
	virtual void operator()() = 0;
	virtual ~EventHandler() = default;
protected:
	BoardGame& board_;
};

class QuitHandler final: public EventHandler
{
public:
	explicit QuitHandler(BoardGame& board,bool& quit): EventHandler(board), quit_(quit){}
	void operator()() noexcept override { this->quit_ = true; }
private:
	bool& quit_;
};

class MouseButtonHandler final: public EventHandler
{
public:
	explicit MouseButtonHandler(BoardGame& board): EventHandler(board) {}
	void operator()() noexcept override { }
};
