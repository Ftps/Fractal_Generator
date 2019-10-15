import os, gi, warnings, sys
gi.require_version('Gtk', '3.0')
from gi.repository import Gtk, Gdk
from collections import Counter

pal_path = "Config/Pallete/"
temp_path = "Config/Temp/"

parameter_name = ["Picture Name:", "Pallete:", "Fractal Type:",
                "Center Real:", "Center Imaginary:", "Pixels X:",
                "Pixels Y:", "Zoom (10^x):", "Power:","Julia Center Real:",
                "Julia Center Imaginary:", "Iterations:", "Conformal Scalar:"]

video = ["Yes", "No"]
fractal = ["Mandelbrot Set", "Julia Set"]

err_msg =  ["All entries must be filled in correctly.", "Image must have a name.",
            "Zoom cannot be bigger than 10^16", "Invalid colour.", "Invalid number.",
            "Pallette must end on a colour without next iterations.",
            "Pallette must have at least two colours."]

RGB = ["R:", "G:", "B:"]
hex = []
for i in range(16):
    hex.append("{0:0{1}x}".format(i,1))

pallete = []

menu_temp = temp_path + "choice.mdb"

class ErrPopup(Gtk.Window):
    def __init__(self, err_name):
        self.timeout_id = None
        self.err = err_name

    def window(self):
        Gtk.Window.__init__(self, title="Error")

        box = []
        for i in range(3):
            box.append(Gtk.Box(spacing=6))

        but_err = Gtk.Button.new_with_label("Continue")
        but_err.connect("clicked", self.cont)
        text_err = Gtk.Label()
        text_err.set_text(self.err)

        grid = Gtk.Grid()
        grid.set_column_homogeneous(True)
        grid.set_row_homogeneous(True)

        grid.attach(box[0], 0, 0, 1, 1)
        grid.attach(text_err, 1, 1, 3, 1)
        grid.attach(box[1], 2, 2, 1, 1)
        grid.attach(but_err, 2, 3, 1, 1)
        grid.attach(box[2], 3, 4, 2, 1)

        self.add(grid)
        self.show_all()

    def cont(self, button):
        Gtk.main_quit()
        self.destroy()

def get_pallete():
    for file in os.listdir(pal_path):
        a, f = os.path.split(file)
        f, a = os.path.splitext(f)
        if Counter(a) == Counter(".pl"):
            pallete.append(f)

def error_detect(val):
    if val == -1:
        return -1

    err_win = ErrPopup(err_msg[val])
    err_win.window()
    err_win.connect('destroy', Gtk.main_quit)
    Gtk.main()
    return val

def print_in_temp(l):
    fp = open(temp_path + "temp.mdb", "w")
    fp.write(l[0] + "\n")

    fp.write(pal_path + l[1] + "\n")

    if l[2] == fractal[1]:
        a = 2
        fp.write("1\n")
    else:
        a = 0
        fp.write("0\n")

    fp.write(str(l[3]) + " " + str(l[4]) + "\n")
    fp.write(str(l[5]) + " " + str(l[6]) + "\n")
    fp.write(str(l[7]) + "\n")
    fp.write(str(l[8]) + "\n")

    if l[2] == fractal[1]:
        fp.write(str(l[9]) + " " + str(l[10]) + "\n")

    fp.write(str(l[9+a]) + "\n")
    fp.write(str(l[10+a]))

def generate_pallette(name, pall):
    pal = []

    for i in range(len(pall)):
        if Counter(pall[i][1]) == Counter("-"):
            pal.append(pall[i][0])
        else:
            l = int(pall[i][1])+1
            beg = [0,0,0]
            end = [0,0,0]
            for j in range(3):
                beg[j] = int(pall[i][0][2*j+1:2*j+3], 16)
                end[j] = int(pall[i+1][0][2*j+1:2*j+3], 16)
            for j in range(l):
                aux = 0
                aux_s = "#"
                for k in range(3):
                    aux = int(round(beg[k] + (end[k]-beg[k])*j//l, 0))
                    aux_s = aux_s + "{0:0{1}x}".format(aux,2)
                pal.append(aux_s)

    fp = open(pal_path + name + ".pl", "w")
    fp.write(str(len(pal)) + "\n")
    for elem in pal:
        fp.write(elem + "\n")
