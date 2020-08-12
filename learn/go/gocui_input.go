package main

import (
	"fmt"
	"log"
	"time"

	"github.com/jroimartin/gocui"
)

// 输出窗口
func viewOutput(g *gocui.Gui, x0, y0, x1, y1 int) error {
	v, err := g.SetView("out", x0, y0, x1, y1)
	if err != nil {
		if err != gocui.ErrUnknownView {
			return err
		}
		v.Wrap = true
		v.Overwrite = false
		v.Autoscroll = true
		v.SelBgColor = gocui.ColorRed
		v.Title = "Messages"
	}
	return nil
}

// 输入窗口（编辑器）
func viewInput(g *gocui.Gui, x0, y0, x1, y1 int) error {
	if v, err := g.SetView("main", x0, y0, x1, y1); err != nil {
		if err != gocui.ErrUnknownView {
			return err
		}
		v.Editable = true
		v.Wrap = true
		v.Overwrite = false
		if _, err := g.SetCurrentView("main"); err != nil {
			return err
		}
		//fmt.Fprintf(v, "fcuk")
	}
	return nil
}

// 显示输出、输入窗口
func layout(g *gocui.Gui) error {
	maxX, maxY := g.Size()
	if err := viewOutput(g, 1, 1, maxX-1, maxY-4); err != nil {
		return err
	}
	if err := viewInput(g, 1, maxY-3, maxX-1, maxY-1); err != nil {
		return err
	}
	return nil
}

// 退出函数
func quit(g *gocui.Gui, v *gocui.View) error {
	return gocui.ErrQuit
}

type VOT struct {
	Msg string
}

func (self VOT) Show(g *gocui.Gui) error {
	v, err := g.View("out")
	if err != nil {
		return nil
	}
	fmt.Fprintf(v, "%v", self.Msg)
	return nil
}

func viewPrint(g *gocui.Gui, msg string) {
	var out VOT
	out.Msg = msg
	g.Update(out.Show)
}

func main() {
	g, err := gocui.NewGui(gocui.OutputNormal)
	if err != nil {
		//log.Panicln(err)
	}

	g.Cursor = true
	g.Mouse = false
	g.ASCII = false

	go func() {
		ticker := time.NewTicker(time.Second)
		for t := range ticker.C {
			s := fmt.Sprintf("ticker %v\n", t)
			viewPrint(g, s)
		}
	}()

	g.SetManagerFunc(layout)
	if err := g.SetKeybinding("main", gocui.KeyCtrlC, gocui.ModNone, quit); err != nil {
		log.Panicln(err)
	}
	if err := g.SetKeybinding("main", gocui.KeyEnter, gocui.ModNone, updateInput); err != nil {
		log.Panicln(err)
	}
	if err := g.MainLoop(); err != nil && err != gocui.ErrQuit {
		log.Panicln(err)
	}
	g.Close()
}

//updateInput 当按下ENTER键时调用，把输入的内容复制到输出窗口中
func updateInput(g *gocui.Gui, cv *gocui.View) error {
	v, err := g.View("out")
	if cv != nil && err == nil {
		var b = make([]byte, 300)
		n, _ := cv.Read(b)
		v.Write([]byte("FUCK:"))
		v.Write(b[:n])
		if n == 0 {
			v.Write([]byte("\n"))
		}
		v.Autoscroll = true
	}
	l := len(cv.Buffer())
	cv.MoveCursor(0-l, 0, true)
	cv.Clear()
	return nil
}
