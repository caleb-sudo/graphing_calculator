import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import geopandas as gpd
import folium
import geodatasets
import contextily as cx

from mpl_toolkits.axes_grid1 import host_subplot
from matplotlib.widgets import RadioButtons, Cursor, CheckButtons 
from matplotlib.backend_bases import MouseEvent, MouseButton

ax = plt.subplots()
a = np.arange(0.0, 2.0, 0.01)
c1 = "1: slope intercept form\n"
c2 = "2: general form NA\n"
c3 = "3: point-slope form NA\n"
c4 = "4: pie chart NA\n"
c5 = "5: scattered plot NA\n"
c6 = "6: bar chart NA\n"
c7 = "7: 3d chart NA\n"
c8 = "8: histogram chart NA\n"
c9 = "9: pre-plotted graphs\n"
c10 = "10: vertex form\n"
c11 = "11: standard form\n"

print("\n",c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10 + c11)

types = input("graph: ")

if types == '1':
    fig = plt.subplot_mosaic([
        ['main', 'color'],
    ],
        width_ratios=[5, 1],
        layout='constrained',
    )

    x = np.linspace(-30, 30, 200, 200)
    m = input("slope: ")
    b = input("y-intercept: ")
    y = int(m)*a + int(b)

    radio_background = 'lightgoldenrodyellow'

    fig['color'].set_facecolor(radio_background)
    radio1 = RadioButtons(
        ax['color'], ('red', 'blue', 'green', 'black'),
        label_props={'color': ['red', 'blue', 'green', 'black']},
        radio_props={
            'facecolor': ['red', 'blue', 'green', 'black'],
            'edgecolor': ['darkred', 'darkblue', 'darkgreen', 'black'],
        }
    )
    line, = fig['main'].plot(a, y, 'o')

    def colorfunc(label):
        line.set_color(label)
        fig.canvas.draw()
    radio1.on_clicked(colorfunc)

elif types == '2':
    print("hello")
elif types == '9':
    fig, ax = plt.subplots()
    gr = input("type: ")
    if gr == 'population':
        df_population = pd.read_csv('pre-plotted_graphs/population/world_pop.csv')
        df_population.plot(x="year", y="value", title="world population 1950-2023")
    if gr == 'map':
        path = geodatasets.get_path("naturalearth.land")
        df = gpd.read_file(path)
        cx.add_basemap(ax)
        df.plot()
    if gr == 'temps':
        df_temps = pd.read_csv('pre-plotted_graphs/temps/average_temps.csv')
        df_temps.plot(x="year", y="temp", title="average yearly temps(Celsius)")
    if gr == 'emmisions':
        df_emmisions = pd.read_csv('pre-plotted_graphs/em/emmisions.csv')
        df_emmisions.plot(x="year", y="amount", alpha=0.8)
        plt.legend(loc='upper left')
    if gr == 'markets':
        type = input("type: ")
        if type == 'resources':
            l_gold, = pd.read_csv('pre-plotted_graphs/markets/resources/gold.csv')
            l_oil, = pd.read_csv('pre-plotted_graphs/markets/resources/oil.csv')
            l_gold.plot(x="time", y="value", visible=False, lw=2, color='yellow')
            l_oil.plot(x="time", y="value", color='black')
            lines_by_label = {l.get_label(): l for l in [l_gold, l_oil]}
            line_colors = [l.get_color() for l in lines_by_label.values()]
            rax = ax.inset_axes([0.0, 0.0, 0.12, 0.2])
            check = CheckButtons(
                ax=rax,
                labels=lines_by_label.keys(),
                actives=[l.get_visible() for l in lines_by_label.values()],
                label_props={'color': line_colors},
                frame_props={'edgecolor': line_colors},
                check_props={'facecolor': line_colors},
            )
            def callback(label):
                ln = lines_by_label[label]
                ln.set_visible(not ln.get_visible())
                ln.figure.canvas.draw_idle()

            check.on_clicked(callback)
elif types == '10':
    x = np.linspace(-30, 30, 300)
    a = input("a: ")
    p = input("p: ")
    q = input("q: ")
    y = int(a)*(x - int(p))**2 + int(q)
    plt.plot(x, y)
elif types == '11':
    x = np.linspace(-30, 30, 300)
    a = input("A: ")
    b = input("B: ")
    c = input("C: ")
    y = int(a)*x**2 + int(b)*x + int(c)
    plt.plot(x, y)

plt.grid(True)
plt.show()