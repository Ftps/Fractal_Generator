import sys, os
sys.path.append(os.path.abspath("Source/Files/GUI"))
from setting import *

import os, gi, warnings
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk
from collections import Counter

class Select_Window(Gtk.Window):
    def __init__(self):
        self.run = 0
        self.name = None
        self.texts = []
        self.entries = []
        self.select = []
        self.good_val = -1
        self.l = None

    def window(self):
        Gtk.Window.__init__(self, title="Image Parameters")

        grid = Gtk.Grid()
        grid.set_column_homogeneous(True)
        grid.set_row_homogeneous(True)

        ok_but = Gtk.Button.new_with_label("Run")
        ok_but.connect("clicked", self.run_math)
        ex_but = Gtk.Button.new_with_label("Exit")
        ex_but.connect("clicked", self.ex_prog)
        vid_but = Gtk.Button.new_with_label("Video Settings")
        vid_but.connect("clicked", self.vid_set)

        box = []
        for i in range(11):
            box.append(Gtk.Box(spacing=6))

        grid.attach(box[0], 0, 0, 1, 1)

        for i in range(len(parameter_name)):
            self.texts.append(Gtk.Label())
            self.texts[i].set_text(parameter_name[i]);
            if i == 0:
                grid.attach(self.texts[0], 1, 1, 2, 1)
                self.name = Gtk.Entry()
                grid.attach(self.name, 3, 1, 7, 1)
            else:
                if i%2 == 0:
                    grid.attach(box[i//2], 5, i//2+1, 1, 1)
                grid.attach(self.texts[i], 5*((i-1)%2)+1, 2 + (i-1)//2, 2, 1)
                if i == 1:
                    self.select.append(Gtk.ComboBoxText())
                    self.select[0].set_entry_text_column(0)
                    for p in pallete:
                        self.select[0].append_text(p)
                    grid.attach(self.select[0], 3, 2, 2, 1)
                elif i == 2:
                    self.select.append(Gtk.ComboBoxText())
                    self.select[1].set_entry_text_column(0)
                    for p in fractal:
                        self.select[1].append_text(p)
                    grid.attach(self.select[1], 8, 2, 2, 1)
                else:
                    self.entries.append(Gtk.Entry())
                    grid.attach(self.entries[i-3], 5*((i-1)%2)+3, 2 + (i-1)//2, 2, 1)

        grid.attach(box[7], 1, 8, 2, 1)
        grid.attach(ok_but, 1, 9, 2, 1)
        grid.attach(box[8], 3, 9, 2, 1)
        grid.attach(vid_but, 5, 9, 2, 1)
        grid.attach(box[9], 7, 9, 2, 1)
        grid.attach(ex_but, 9, 9, 2, 1)
        grid.attach(box[10], 11, 10, 1, 1)


        self.add(grid)
        self.show_all()

    def run_math(self, button):
        self.run = 1
        self.good_val = -1
        self.l = []
        self.l.append(self.name.get_text())

        if Counter(self.l[0]) == Counter(""):
            self.good_val = 1
            Gtk.main_quit()
            return
        elif self.get_sel(0) in pallete and self.get_sel(1) in fractal:
            self.l.append(self.get_sel(0) + ".pl")
            self.l.append(self.get_sel(1))
        else:
            self.good_val = 0
            Gtk.main_quit()
            return

        for i in range(len(self.entries)):
            try:
                if i//2 == 1 or i == 8:
                    self.l.append(int(self.entries[i].get_text()))
                elif i//2 == 3:
                    if self.l[2] == fractal[1]:
                        self.l.append(float(self.entries[i].get_text()))
                else:
                    self.l.append(float(self.entries[i].get_text()))
            except:
                self.good_val = 0
                Gtk.main_quit()
                return

        if self.l[8] > 16:
            self.good_val = 2
        Gtk.main_quit()

    def ex_prog(self, button):
        Gtk.main_quit()

    def vid_set(self, button):
        print("Video")

    def ret_run(self):
        return self.run

    def set_run(self, r):
        self.run = r

    def ret_good(self):
        return self.good_val

    def get_sel(self, i):
        iter = self.select[i].get_active_iter()
        if iter is not None:
            m = self.select[i].get_model()
            return m[iter][0]
        else:
            return None

    def get_list(self):
        return self.l



if __name__ == '__main__':
    get_pallete()
    win = Select_Window()
    win.window()
    win.connect('destroy', Gtk.main_quit)
    while 1:
        win.set_run(0)
        Gtk.main()
        if win.ret_run() == 0:
            sys.exit(0)
        elif error_detect(win.ret_good()) == -1:
            print_in_temp(win.get_list())
            break
