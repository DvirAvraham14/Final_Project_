#pragma once 

class Screen {
public:
	Screen() = default;
	 void setScreen(T_Screen screen) { m_screen = screen; };
	 auto getScreen() { return m_screen; };
	 Screen(const Screen&) ;
private:
	T_Screen m_screen = T_Screen::Menu;
};