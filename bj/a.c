#include <stdio.h>
#include <stdlib.h>
#include <acllib.h>

// 编辑框的大小和位置
#define EDITOR_WIDTH 600
#define EDITOR_HEIGHT 100
#define EDITOR_X 100
#define EDITOR_Y 100

// 编辑框最多可以输入的字符数
#define EDITOR_LIMIT 100

    typedef struct
{
    char text[EDITOR_LIMIT]; // 编辑框文本内容
    int length;              // 编辑框文本长度
    int cursorPos;           // 光标位置
    int isEnabled;          // 是否启用光标
} Editor;

// 定义编辑框
Editor editor;

int timerId = 0;           // 定时器ID
int isCursorShown = 1; // 光标是否显示

// 定时器回调函数：用于控制光标闪烁
void TimerEvent(int timerId)
{
    isCursorShown = !isCursorShown;
    beginPaint();
    setPenColor(BLACK);
    if (isCursorShown && editor.isEnabled)
    { // 如果光标在闪烁且启用，则绘制光标
        int cursorX = EDITOR_X + 10 + getTextWidth(editor.text, editor.cursorPos);
        int cursorY = EDITOR_Y + 10;
        rectangle(cursorX, cursorY, cursorX + 2, cursorY + 20);
    }
    else
    { // 否则擦除光标
        int cursorX = EDITOR_X + 10 + getTextWidth(editor.text, editor.cursorPos);
        int cursorY = EDITOR_Y + 10;
        setBrushColor(WHITE);
        rectangle(cursorX, cursorY, cursorX + 2, cursorY + 20);
    }
    endPaint();
}

// 鼠标事件回调函数：用于设置光标位置
void onMouseEvent(int x, int y, int button, int event)
{
    if (button == LEFT_BUTTON && event == BUTTON_DOWN)
    {
        // 如果鼠标点击在文本区域，则设置光标位置
        if (x >= EDITOR_X + 10 && x <= EDITOR_X + 10 + getTextWidth(editor.text, editor.length) && y >= EDITOR_Y + 10 && y <= EDITOR_Y + 30)
        {
            editor.cursorPos = (x - EDITOR_X - 10) / 10;
        }
    }
}

// 键盘事件回调函数：用于对编辑框进行操作
void onKeyboardEvent(int key, int event)
{
    if (event == KEY_DOWN)
    {
        if (key == VK_BACK)
        { // 如果按下退格键，则删除光标前的一个字符
            if (editor.cursorPos > 0)
            {
                for (int i = editor.cursorPos - 1; i < editor.length; i++)
                {
                    editor.text[i] = editor.text[i + 1];
                }
                editor.cursorPos--;
                editor.length--;
            }
        }
        else if (key == VK_DELETE)
        { // 如果按下删除键，则删除光标后的一个字符
            if (editor.cursorPos < editor.length)
            {
                for (int i = editor.cursorPos; i < editor.length; i++)
                {
                    editor.text[i] = editor.text[i + 1];
                }
                editor.length--;
            }
        }
        else if (key == VK_LEFT)
        { // 如果按下左箭头，则移动光标位置
            editor.cursorPos = (editor.cursorPos > 0) ? editor.cursorPos - 1 : 0;
        }
        else if (key == VK_RIGHT)
        { // 如果按下右箭头，则移动光标位置
            editor.cursorPos = (editor.cursorPos < editor.length) ? editor.cursorPos + 1 : editor.length;
        }
        else if (key == VK_HOME)
        { // 如果按下Home键，则将光标移动到开头
            editor.cursorPos = 0;
        }
        else if (key == VK_END)
        { // 如果按下End键，则将光标移动到结尾
            editor.cursorPos = editor.length;
        }
        else if (key == VK_INSERT)
        { // 如果按下Insert键，则启用或禁用光标
            editor.isEnabled = !editor.isEnabled;
            if (editor.isEnabled)
            {
                timerId = SetTimer(TimerEvent, 500); // 启动定时器来控制光标闪烁
            }
            else
            {
                KillTimer(timerId); // 禁用光标时停止定时器
            }
        }
        else if (key == VK_RETURN)
        { // 如果按下回车键，则输出内容并退出程序
            editor.isEnabled = 0;
            killTimer(timerId);
            printf("%s\n", editor.text);
            exit(0);
        }
        else if ((key >= 'a' && key <= 'z') || (key >= 'A' && key <= 'Z') || (key >= '0' && key <= '9') || key == ' ')
        {
            // 如果按下字母、数字或空格键，则在光标处插入字符
            if (editor.length < EDITOR_LIMIT)
            {
                for (int i = editor.length; i > editor.cursorPos; i--)
                {
                    editor.text[i] = editor.text[i - 1];
                }
                editor.text[editor.cursorPos] = key;
                editor.cursorPos++;
                editor.length++;
            }
        }
    }
}

// 初始化函数：绘制编辑框
int Setup()
{
    // 初始化窗口和事件回调函数
    initWindow("Editor", DEFAULT, DEFAULT, EDITOR_WIDTH, EDITOR_HEIGHT);
    registerMouseEvent(onMouseEvent);
    registerKeyboardEvent(onKeyboardEvent);

    // 初始化编辑框
    editor.isEnabled = 0;

    // 绘制编辑框外框
    beginPaint();
    clearDevice();
    rectangle(EDITOR_X, EDITOR_Y, EDITOR_X + 500, EDITOR_Y + 50);
    endPaint();

    return 0;
}

// gcc ..\acllib\acllib.c a.c -I..\acllib -lgdi32 -lole32 -loleaut32 -luuid -lwinmm -lmsimg32 -DWINVER=0x0501 -o a