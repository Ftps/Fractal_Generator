import sys, os
sys.path.append(os.path.abspath("Source/Files/GUI"))
from setting import *

import os, gi, warnings
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk
from collections import Counter

class DevNull:
    def write(self, msg):
        pass

#sys.stderr = DevNull()

class Select_Window(Gtk.Window):
    def __init__(self):
        self.select = 0

    def window(self):
        Gtk.Window.__init__(self, title="Fractal Image Generator - F.I.G.")

        grid = Gtk.Grid()
        grid.set_column_homogeneous(True)
        grid.set_row_homogeneous(True)

        box1 = Gtk.Box(spacing=6)
        box2 = Gtk.Box(spacing=6)
        box3 = Gtk.Box(spacing=6)

        grid.attach(box1, 0, 0, 1, 1)

        pic_but = Gtk.Button.new_with_label("Generate Fractal Image")
        pic_but.connect("clicked", self.pic)
        pal_but = Gtk.Button.new_with_label("Generate New Pallete")
        pal_but.connect("clicked", self.pal)

        grid.attach(pic_but, 1, 1, 1, 1)
        grid.attach(box2, 1, 2, 1, 1)
        grid.attach(pal_but, 1, 3, 1, 1)
        grid.attach(box3, 2, 4, 1, 1)

        self.add(grid)
        self.show_all()

    def pic(self, button):
        self.select = 1
        self.destroy()

    def pal(self, button):
        self.select = 2
        self.destroy()

    def sel(self):
        return self.select

if __name__ == '__main__':
    win = Select_Window()
    win.window()
    win.connect('destroy', Gtk.main_quit)
    while 1:
        Gtk.main()
        if win.sel() == 0:
            sys.exit(0)
        elif win.sel() == 1:
            fp = open(menu_temp, "w")
            fp.write("1")
            fp.close()
            break
        else:
            fp = open(menu_temp, "w")
            fp.write("0")
            fp.close()
            break
