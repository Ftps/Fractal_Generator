import sys, os
sys.path.append(os.path.abspath("Source/Files/GUI"))
from setting import *

import gi, warnings
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk
from collections import Counter
from random import randint

pal = []

class Select_Conver(Gtk.Window):
    def __init__(self):
        self.good = 0
        self.run = 0
        self.entry = None
        self.col = ""

    def window(self):
        Gtk.Window.__init__(self, title="Pallete Generator")

        self.set_default_size(200,200)
        self.set_hexpand(False)

        grid = Gtk.Grid()
        grid.set_column_homogeneous(True)
        grid.set_row_homogeneous(True)

        ok_but = Gtk.Button.new_with_label("Select")
        ok_but.connect("clicked", self.slct)
        ex_but = Gtk.Button.new_with_label("Exit")
        ex_but.connect("clicked", self.exit)

        box = []
        for _ in range(4):
            box.append(Gtk.Box(spacing=600))

        grid.attach(box[0], 0, 0, 1, 1)
        text = Gtk.Label()
        text.set_text("Select color for converging points (eg. #ff00ff, FF00FF)")
        grid.attach(text, 1, 1, 3, 1)

        text2 = Gtk.Label()
        text2.set_text("Colour:")
        grid.attach(text2, 1, 2, 1, 1)

        self.entry = Gtk.Entry()
        grid.attach(self.entry, 2, 2, 2, 1)

        grid.attach(box[1], 1, 3, 2, 1)
        grid.attach(ok_but, 1, 4, 1, 1)
        grid.attach(box[2], 2, 4, 1, 1)
        grid.attach(ex_but, 3, 4, 1, 1)
        grid.attach(box[3], 4, 5, 1, 1)

        self.add(grid)
        self.show_all()

    def slct(self, button):
        self.good = -1
        self.run = 1

        self.col = self.entry.get_text()
        if len(self.col) < 6:
            self.good = 3
            Gtk.main_quit()
            return

        if self.col[0] != "#":
            self.col = "#" + self.col

        self.col = self.col.lower()

        for i in range(1, 7):
            if self.col[i] not in hex:
                self.good = 3
                Gtk.main_quit()
                return

        self.col = self.col[:7]
        self.destroy()
        Gtk.main_quit()

    def exit(self, button):
        Gtk.main_quit()

    def ret_run(self):
        return self.run

    def set_run(self, r):
        self.run = r

    def ret_good(self):
        return self.good

    def get_col(self):
        return self.col


class Select_Window(Gtk.Window):
    def __init__(self, col):
        self.past_option = 0
        self.run = 0
        self.good = -1
        self.add_l = None
        self.color = None
        self.linear = None
        self.col = col
        self.grid = Gtk.Grid()
        self.name = None
        self.pallette = ""

        self.liststore = Gtk.ListStore(str, str)
        self.liststore.append([col, "-"])

        self.treeview = Gtk.TreeView(self.liststore)
        cell = Gtk.CellRendererText()
        cell.set_property("font", "Sans Bold 15")
        column = Gtk.TreeViewColumn("Colour", cell, text=0, background=0)
        column.set_fixed_width(250)
        self.treeview.append_column(column)

        cell = Gtk.CellRendererText()
        column = Gtk.TreeViewColumn("Iterations Until Next Color", cell, text=1)
        self.treeview.append_column(column)

    def window(self):
        Gtk.Window.__init__(self, title="Pallette Generator")

        self.grid.set_column_homogeneous(True)
        self.grid.set_row_homogeneous(True)

        box = []
        for _  in range(12):
            box.append(Gtk.Box(spacing=6))

        gen_but = Gtk.Button.new_with_label("Generate")
        gen_but.connect("clicked", self.generate)
        exi_but = Gtk.Button.new_with_label("Exit")
        exi_but.connect("clicked", self.exit)

        add_c = Gtk.Button.new_with_label("Add")
        add_c.connect("clicked", self.add_color)
        self.add_l = Gtk.Button.new_with_label("Change")
        self.add_l.connect("clicked", self.add_linear)

        add_r = Gtk.Button.new_with_label("Add Random")
        add_r.connect("clicked", self.add_random)
        del_a = Gtk.Button.new_with_label("Clear Pallette")
        del_a.connect("clicked", self.delete_all)
        del_l = Gtk.Button.new_with_label("Delete Last")
        del_l.connect("clicked", self.delete_last)

        self.grid.attach(box[0], 0, 0, 1, 1)

        text = Gtk.Label()
        text.set_text("Pallette Name:")
        self.grid.attach(text, 1, 1, 1, 1)

        self.name = Gtk.Entry()
        self.grid.attach(self.name, 2, 1, 2, 1)
        self.grid.attach(box[1], 1, 2, 5, 1)

        color = Gtk.Label()
        color.set_text("Colour:")
        self.grid.attach(color, 1, 3, 1, 1)
        self.color = Gtk.Entry()
        self.grid.attach(self.color, 2, 3, 2, 1)
        self.grid.attach(box[1], 4, 3, 1, 1)
        self.grid.attach(add_c, 5, 3, 1, 1)

        self.grid.attach(box[2], 1, 4, 5, 1)

        linear = Gtk.Label()
        linear.set_text("Lin. Interpol.:")
        self.grid.attach(linear, 1, 5, 1, 1)
        self.linear = Gtk.Entry()
        self.grid.attach(self.linear, 2, 5, 2, 1)
        self.grid.attach(box[3], 4, 5, 1, 1)
        self.grid.attach(self.add_l, 5, 5, 1, 1)

        self.grid.attach(box[4], 1, 6, 5, 1)

        self.grid.attach(add_r, 1, 7, 1, 1)
        self.grid.attach(box[5], 2, 7, 1, 1)
        self.grid.attach(del_a, 3, 7, 1, 1)
        self.grid.attach(box[6], 4, 7, 1, 1)
        self.grid.attach(del_l, 5, 7, 1, 1)

        self.grid.attach(box[7], 1, 8, 5, 1)

        self.grid.attach(self.treeview, 1, 9, 5, 4)

        self.grid.attach(box[8], 1, 13, 5, 1)
        self.grid.attach(gen_but, 1, 14, 2, 1)
        self.grid.attach(box[9], 3, 14, 1, 1)
        self.grid.attach(exi_but, 4, 14, 2, 1)
        self.grid.attach(box[10], 6, 15, 1, 1)

        self.add(self.grid)
        self.show_all()


    def generate(self, button):
        self.run = 1

        self.pallette = self.name.get_text().replace(" ", "_")

        if Counter(self.pallette) == Counter(""):
            self.good = 1
        elif len(self.liststore) == 1:
            self.good = 6
        elif Counter(self.liststore[len(self.liststore)-1][1]) != Counter("-"):
            self.good = 5
        else:
            self.good = -1

        Gtk.main_quit()
        return

    def exit(self, button):
        Gtk.main_quit()


    def add_color(self, button):
        col = self.color.get_text()
        col.replace(" ", "")

        if col[0] != "#":
            col = "#" + col

        if len(col) != 7:
            self.run = 1
            self.good = 3
            Gtk.main_quit()
            return

        col = col.lower()

        for i in range(1, 7):
            if col[i] not in hex:
                self.run = 1
                self.good = 3
                Gtk.main_quit()
                return

        self.liststore.append([col, "-"])

    def add_linear(self, button):
        try:
            a = int(self.linear.get_text())
            if a < 1:
                self.liststore[len(self.liststore)-1][1] = "-"
                return
        except:
            self.run = 1
            self.good = 4
            Gtk.main_quit()
            return

        self.liststore[len(self.liststore)-1][1] = self.linear.get_text()


    def add_random(self, button):
        col = "#"
        for _ in range(3):
            col = col + "{0:0{1}x}".format(randint(0,255),2)
        self.liststore.append([col, "-"])

    def delete_all(self, button):
        while len(self.liststore) > 1:
            iter = self.liststore[1]
            self.liststore.remove(iter.iter)
        self.liststore[0][1] = "-"

    def delete_last(self, button):
        if len(self.liststore) > 1:
            iter = self.liststore[len(self.liststore)-1]
            self.liststore.remove(iter.iter)



    def set_run(self, r):
        self.run = r

    def ret_run(self):
        return self.run

    def ret_good(self):
        return self.good

    def get_name(self):
        return self.pallette

    def get_pallette(self):
        return self.liststore



if __name__ == "__main__":
    win = Select_Conver()
    win.window()
    win.connect('destroy', Gtk.main_quit)
    while 1:
        win.set_run(0)
        Gtk.main()
        if win.ret_run() == 0:
            sys.exit(0)
        elif error_detect(win.ret_good()) == -1:
            pal.append(win.get_col())
            break

    win = Select_Window(pal[0])
    win.window()
    win.connect('destroy', Gtk.main_quit)
    while 1:
        win.set_run(0)
        Gtk.main()
        if win.ret_run() == 0:
            sys.exit(0)
        elif error_detect(win.ret_good()) == -1:
            generate_pallette(win.get_name(), win.get_pallette())
            break
