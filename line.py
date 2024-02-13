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
    if gr == '1':
        type = input("type: ")
        if type == '1':
            df = pd.read_csv('pre-plotted_graphs/markets/resources.csv', index_col='time')
            times = df.index
            oil_val = df['oil_value']
            oil_vol = df['oil_volume']
            gold_val = df['gold_value']
            gold_vol = df['gold_volume']
            copper_val = df['copper_value']
            copper_vol = df['copper_volume']
            silver_val = df['silver_value']
            silver_vol = df['silver_volume']
            platinum_val = df['platinum_value']
            platinum_vol = df['platinum_volume']
            lumber_val = df['lumber_value']
            lumber_vol = df['lumber_volume']
            
            fig, ax = plt.subplots()

            l0, = ax.plot(times, oil_val)
            l1, = ax.plot(times, gold_val)
            l2, = ax.plot(times, copper_val)
            l3, = ax.plot(times, silver_val)
            l4 = ax.plot(times, platinum_val)
            l5 = ax.plot(times, lumber_val)
            lines = (l0, l1, l2, l3, l4, l5)

            def setVisible(label_name):
                option_indx = choices.index(label_name)
                line = lines[option_indx]
                line.set_visible(not line.get_visible())
                plt.draw()
            choices = ('oil', 'gold', 'copper')
            check_state = (True, False, False)
            ax_checkbox = plt.axes([0.0, 0.0, 0.12, 0.2])
            checkbox = CheckButtons(ax_checkbox, choices, check_state)
            checkbox.on_clicked(setVisible)
            for i, line in enumerate(lines):
                line.set_visible(check_state[i])
        if type == 'companies':
            df = pd.read_csv('pre-plotted_graphs/markets/companies.csv', index_col='time')
            times= df.index

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
plt.show()
