#include <lib/printf.h>
#include <lib/graphics.h>
#include <gfx/events.h>
#include <colors.h>

class Editor : public Window {  
public:  
	Editor() : Window(288, 248, "Editor") {
		m_x = 0;
		m_y = 0;
		m_textBuffer = (unsigned char*) malloc((c_width/8)*(c_height/8));
		gfx_draw_rectangle(0, 0, 288, 248, COLOR_BOX_LIGHT_FG);
		gfx_draw_line(17, 0, 17, 248, 0xff);
		for (int i = 0; i < 248; i++){
			gfx_draw_format_text(0, i*8, 0xff, "%s%d ", i < 10 ? " " : "", i);
		}
	}

	~Editor() {
		free(m_textBuffer);
		close(m_fd);
	}

	void Save();
	void Open(char* path);
	void putChar(unsigned char c);
	void EditorLoop();

private:
	int m_fd = -1;
	unsigned char* m_textBuffer;
	int m_bufferSize = 0;
	int m_x, m_y;

	/* Size is based on the fact that our filesystem can only handle 8kb files */
	const int c_width = 280;
	const int c_height = 240;

	void reDraw();
};

void Editor::reDraw()
{	
	m_x = 0;
	m_y = 0;
	gfx_draw_rectangle(0, 0, 288, 248, COLOR_BOX_LIGHT_FG);
	gfx_draw_line(17, 0, 17, 248, 0xff);
	for (int i = 0; i < 248; i++){
		gfx_draw_format_text(0, i*8, 0xff, "%s%d ", i < 10 ? " " : "", i);
	}
	for (int i = 0; i < m_bufferSize; i++){
		putChar(m_textBuffer[i]);
	}
}

void Editor::Open(char* path)
{
	m_fd = open(path);
	if(m_fd <= 0)
		return;
	
	m_bufferSize = read(m_fd, m_textBuffer, (c_width/8)*(c_height/8));
	reDraw();
	
}


void Editor::EditorLoop()
{
	while (1){
		struct gfx_event event;
		gfx_get_event(&event);
		switch (event.event){
		case GFX_EVENT_KEYBOARD:
			m_bufferSize++;
			putChar(event.data);
			if(event.data == '\n')
				reDraw();
			break;
		default:
			break;
		}
	}
}

void Editor::putChar(unsigned char c)
{	
	if(c != '\b')
		m_textBuffer[m_y*(c_width/8) + m_x] = c;
	gfx_draw_rectangle(24 + m_x*8, m_y*8, 8, 8, COLOR_BOX_LIGHT_FG);

	switch (c){
	case '\n':
		m_x = (c_width/8)+1;
		break;;
	case '\b':
		if(m_x == 0) return;
		m_x--;
		m_bufferSize--;
		//gfx_draw_rectangle(24 + m_x*8, m_y*8, 8, 8, COLOR_BOX_LIGHT_FG);
		//gfx_draw_char(24 + m_x*8, m_y*8, '_', COLOR_BOX_BG);
		return;
	case 254:
		if(m_x == 0 || m_y == 0) return;
		gfx_draw_rectangle(24 + m_x*8, m_y*8, 8, 8, COLOR_BOX_LIGHT_FG);
		gfx_draw_char(24 + m_x*8, m_y*8, m_textBuffer[m_y*(c_width/8) + m_x], COLOR_BOX_LIGHT_FG);

		m_y--;
		gfx_draw_char(24 + m_x*8, m_y*8, '_', COLOR_BOX_BG);
		return;
	default:
		gfx_draw_char(24 + m_x*8, m_y*8, c, COLOR_BOX_BG);
		break;
	}

	m_x++;
	if(m_x > (c_width/8) + 8){
		m_x = 0;
		m_y++;
	}

	gfx_draw_char(24 + m_x*8, m_y*8, '_', COLOR_BOX_BG);
}

int main()
{
	//for (int i = 0; i < argc; i++){
	//	printf("argv: %s\n", argv[i]);
	//}
	

    Editor s1;
	s1.Open("/home");
	s1.EditorLoop();

	printf("Done\n");
	return 0;
}