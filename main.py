import matplotlib
import matplotlib.animation as animation
matplotlib.use("TkAgg")

from matplotlib.backends.backend_tkagg import FigureCanvasTkAgg, NavigationToolbar2Tk
from matplotlib.figure import Figure
from matplotlib import style
from sklearn import datasets
import tkinter as tk
from tkinter import ttk
import yfinance as yf

import urllib
import json
import requests
import pandas as pd
import numpy as np


Large_font = ("verdana", 12)
style.use("ggplot")

f = Figure(figsize=(5,5), dpi=100)
a = f.add_subplot(111)
    



class grapher(tk.Tk):
    def __init__(self, *args, **kwargs):

        tk.Tk.__init__(self, *args, **kwargs)

        tk.Tk.wm_title(self, "hampter")

        container = tk.Frame(self)
        container.pack(side="top", fill="both", expand=True)
        container.grid_rowconfigure(0, weight=1)
        container.grid_columnconfigure(0, weight=1)

        self.frames = {}

        for F in (StartPage, PageOne, PageTwo, PageThree):

            frame = F(container, self)

            self.frames[F] = frame

            frame.grid(row=0, column=0, sticky="nsew")

        self.show_frame(StartPage)
    def show_frame(self, cont):
        frame = self.frames[cont]
        frame.tkraise()

class StartPage(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = ttk.Label(self, text="menu", font=Large_font)
        label.pack(padx=10, pady=10)

        button1 = ttk.Button(self, text="Page one", command=lambda: controller.show_frame(PageOne))
        button1.pack()

        button2 = ttk.Button(self, text="Page Two", command=lambda: controller.show_frame(PageTwo))
        button2.pack()

        button2 = ttk.Button(self, text="graph", command=lambda: controller.show_frame(PageThree))
        button2.pack()

class PageOne(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = ttk.Label(self, text="Page one", font=Large_font)
        label.pack(padx=10, pady=10)

        button1 = ttk.Button(self, text="back", command=lambda: controller.show_frame(StartPage))
        button1.pack()

class PageTwo(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Page one", font=Large_font)
        label.pack(padx=10, pady=10)

        button1 = ttk.Button(self, text="back", command=lambda: controller.show_frame(StartPage))
        button1.pack()

class PageThree(tk.Frame):
    def __init__(self, parent, controller):
        tk.Frame.__init__(self, parent)
        label = tk.Label(self, text="Page three", font=Large_font)
        label.pack(padx=10, pady=10)

        button1 = ttk.Button(self, text="back", command=lambda: controller.show_frame(StartPage))
        button1.pack()

        data = yf.download('XOM', start="1950-01-01", end="2020-12-31")
        microsoft = yf.download('MSFT', start="1950-01-01", end="2020-12-31")
        ibm = yf.download('IBM', start="1950-01-01", end="2020-12-31")

    
        a.clear()
         
        a.plot(data)
        a.plot(microsoft)
        a.plot(ibm)

        canvas = FigureCanvasTkAgg(f, self)
        canvas.get_tk_widget().pack(side=tk.TOP, fill=tk.BOTH, expand=True)

        toolbar = NavigationToolbar2Tk(canvas, self)
        toolbar.update()
        canvas._tkcanvas.pack(side=tk.TOP, fill=tk.BOTH, expand=True)





app = grapher()
app.mainloop()