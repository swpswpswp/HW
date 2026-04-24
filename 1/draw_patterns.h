#pragma once
class draw_patterns 
{
public:
	int m_h;
	char m_char;
	draw_patterns(int h = 3, char c = '*') :m_h(h), m_char(c) {}
	~draw_patterns() {};
	void mb_draw();
	void mb_input();
};