import matplotlib
matplotlib.use("TkAgg")
import tkinter as tk
import pandas as pd
import numpy as np

from datasets.val import *

from tkinter import ttk
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure

class main(tk.Tk):
    def __init__(self, *args, **kwargs):
        tk.Tk.__init__(self, *args, **kwargs)
                
        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand = True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        for f in (start, gcalc, pre_plotted, norm):
            frame = f(container, self)
            self.frames[f] = frame
            frame.grid(row=0, column=0, sticky="nsew")

    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()
            

class start(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        graphcalc = ttk.Button(self, text="graphing calulator", command=lambda: controller.show_frame(gcalc))
        graphcalc.pack()
        pre = ttk.Button(self, text="pre-plotted graphs", command=lambda: controller.show_frame(pre_plotted))
        pre.pack()
        normal = ttk.Button(self, text="normal calculator", command=lambda: controller.show_frame(norm))
        normal.pack()

class gcalc(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(start))
        back.pack()

        f = Figure(figsize=(5,5), dpi=100)
        a = f.add_subplot(111)

        a.plot(time, lines)
        canvas = FigureCanvasTkAgg(f, self)
        canvas.draw()
        canvas.get_tk_widget().pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)

        toolbar = NavigationToolbar2Tk(canvas, self)
        toolbar.update()
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

class pre_plotted(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(start))
        back.pack()
        emmision = ttk.Button(self, text="emmisions", command=lambda: controller.show_frame(em))
        emmision.pack()
        mark = ttk.Button(self, text="markets", command=lambda: controller.show_frame(markets))
        mark.pack()
        pop = ttk.Button(self, text="population", command=lambda: controller.show_frame(population))
        pop.pack()
        temp = ttk.Button(self, text="tempatures", command=lambda: controller.show_frame(temps))
        temp.pack()

class norm(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        
        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(start))
        back.pack()

class em(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(pre_plotted))
        back.pack()

class markets(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(pre_plotted))
        back.pack()
        comp = ttk.Button(self, text="companies", command=lambda: controller.show_frame(company))
        comp.pack()
        crypt = ttk.Button(self, text="crypto value", command=lambda: controller.show_frame(crypto))
        crypt.pack()
        gdp = ttk.Button(self, text="GDP", command=lambda: controller.show_frame(GDP))
        gdp.pack()
        resource = ttk.Button(self, text="resources", command=lambda: controller.show_frame(resources))
        resource.pack()


class population(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(pre_plotted))
        back.pack()

class temps(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(pre_plotted))
        back.pack()

class company(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(markets))
        back.pack()

class crypto(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(markets))
        back.pack()

class GDP(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(markets))
        back.pack()

class resources(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame(self, parent)

        back = ttk.Button(self, text="go back", command=lambda: controller.show_frame(markets))
        back.pack()

app = main()
app.mainloop()