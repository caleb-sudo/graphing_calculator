import matplotlib
matplotlib.use("TkAgg")
from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
import matplotlib.animation as animation
from matplotlib import style
from tkinter import *
import tkinter as tk
from tkinter import ttk
import ipywidgets as widgets

import urllib
import json
import matplotlib.pyplot as plt
import pandas as pd
import numpy as np
from lists import *

LARGE_FONT= ("Verdana", 12)
style.use("ggplot")

f = Figure(figsize=(5,5), dpi=100)
a = f.add_subplot(111)

class mainpage(tk.Tk):
    def __init__(self, *args, **kwargs):
        
        tk.Tk.__init__(self, *args, **kwargs)

        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand = True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        for F in (start, graph, pre):
            frame = F(container, self)

            self.frames[F] = frame

            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(start)

    def show_frame(self, cont):

        frame = self.frames[cont]
        frame.tkraise()

class start(tk.Frame):

    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        label = tk.Label(self, text="Start Page", font=LARGE_FONT)
        label.pack(pady=10,padx=10)

        graph_button = ttk.Button(self, text="graphing", command=lambda: controller.show_frame(graph))
        graph_button.pack()

        preplotted_button = ttk.Button(self, text="pre-plotted graphs", command=lambda: controller.show_frame(pre))
        preplotted_button.pack()

class graph(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        label = tk.Label(self, text="graphing", font=LARGE_FONT)
        label.pack(pady=10,padx=10)

        back_button = ttk.Button(self, text="Back", command=lambda: controller.show_frame(start))
        back_button.pack()

class pre(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self,parent)
        label = tk.Label(self, text="pre-plotted graphs", font=LARGE_FONT)
        label.pack(pady=10,padx=10)

        back_button = ttk.Button(self, text="back", command=lambda: controller.show_frame(start))
        back_button.pack()

        clicked = StringVar()
        clicked.set(opts[1])

        drop = OptionMenu(self, clicked, *opts, command=clicked.get()) 
        drop.pack()

        label = Label(self, text="") 
        label.pack()


        canvas = FigureCanvasTkAgg(f, self)
        canvas.get_tk_widget().pack(side=tk.BOTTOM, fill=tk.BOTH, expand=True)

        toolbar = NavigationToolbar2Tk(canvas, self)
        toolbar.update()
        canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        if (opts[0] == True):
            df = pd.read_csv('pre_plotted_graphs/data/em/emmisions.csv', index_col='year')
            time = df.index
            a.clear()
            a.plot(time, df, label=ems)
            a.legend()
        elif (opts[1] == True):
            df = pd.read_csv('pre_plotted_graphs/data/markets/companies_val.csv', index_col='time')
            time = df.index
            a.clear()
            a.plot(time, df)
        elif (opts[2] == True):
            df = pd.read_csv('pre_plotted_graphs/data/markets/companies_vol.csv', index_col='time')
            time = df.index
            a.clear()
            a.plot(time, df)
        elif (opts[3] == True):
            df = pd.read_csv('pre_plotted_graphs/data/temps/average_temps.csv', index_col='year')
            time = df.index
            a.clear()
            a.plot(time, df)

app = mainpage()
app.mainloop()