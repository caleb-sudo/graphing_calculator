import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import geopandas as gpd
import folium
import geodatasets
import contextily as cx
import math

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
c12 = "l2: quadradic solver\n"

print("\n",c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10 + c11 +c12)

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
    y = int(m)*x + int(b)

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
    elif gr == 'map':
        path = geodatasets.get_path("naturalearth.land")
        df = gpd.read_file(path)
        cx.add_basemap(ax)
        df.plot()
    elif gr == 'temps':
        df_temps = pd.read_csv('pre-plotted_graphs/temps/average_temps.csv')
        df_temps.plot(x="year", y="temp", title="average yearly temps(Celsius)")
    elif gr == 'emmisions':
        df = pd.read_csv('pre-plotted_graphs/em/emmisions.csv', index_col='year')
        year = df.index
        africa = df['Africa']
        asia = df['Asia']
        north_america = df['North_America']
        oceania = df['Ocieana']
        south_america = df['South_America']
        world = df['World']
        fig, ax = plt.subplots()
        l1, = ax.plot(year, world)
        l2, = ax.plot(year, africa)
        l3, = ax.plot(year, asia)
        l4, = ax.plot(year, north_america)
        l5, = ax.plot(year, south_america)
        l6, = ax.plot(year, oceania)
        lines = (l1, l2, l3, l4, l5, l6)
        
        choices_plotted = ('World', 'Africa', 'Aisa', 'North_america', 'South_america', 'Oceania')
        check_state = (True, False, False, False, False, False)
    elif gr == 'markets':
        type = input("type: ")
        if type == '1':
            df = pd.read_csv('pre-plotted_graphs/markets/resources.csv', index_col='time')
            times = df.index
            oil_val = df['oil_val']
            oil_vol = df['oil_vol']
            gold_val = df['gold_val']
            gold_vol = df['gold_vol']
            copper_val = df['copper_val']
            copper_vol = df['copper_vol']
            silver_val = df['silver_val']
            silver_vol = df['silver_vol']
            platinum_val = df['platinum_val']
            platinum_vol = df['platinum_vol']
            
            fig, ax = plt.subplots()
            choice2 = input("type: ")
            if choice2 == 'value':
                l0, = ax.plot(times, oil_val)
                l1, = ax.plot(times, gold_val)
                l2, = ax.plot(times, copper_val)
                l3, = ax.plot(times, silver_val)
                l4, = ax.plot(times, platinum_val)
                lines = (l0, l1, l2, l3, l4)
            elif choice2 == 'volume':
                l0, = ax.plot(times, oil_vol)
                l1, = ax.plot(times, gold_vol)
                l2, = ax.plot(times, copper_vol)
                l3, = ax.plot(times, silver_vol)
                l4, = ax.plot(times, platinum_vol)
                lines = (l0, l1, l2, l3, l4)
                 
            choices_plotted = ('oil', 'gold', 'copper', 'silver', 'platinum')
            check_state = (True, False, False, False, False)

        elif type == 'companies':
            df = pd.read_csv('pre-plotted_graphs/markets/companies.csv', index_col='time')
            time = df.index

            apple_val = df['apple_value']
            microsoft_val = df['microsoft_value']
            walmart_val = df['walmart_value']
            mcdonalds_val = df['McDonalds_value']
            tesla_val = df['tesla_value']
            meta_val = df['meta_value']
            bilibili_val = df['bilibili_value']
            intel_val = df['intel_value']
            amazon_val = df['amazon_value']
            nvidia_val = df['nvidia_value']
            IBM_val = df['IBM_value']
            shopify_val = df['shopify_value']
            telus_val = df['telus_value']
            honda_val = df['honda_value']
            general_motors_val = df['general-motors_value']
            toyota_val = df['toyota_value']
            ford_val = df['ford_value']
            sony_val = df['sony_value']
            dell_val = df['dell_value']
            netflix_val = df['netflix_value']
            alphabet_val = df['alphabet_value']
            spotify_val = df['spotify_value']
            disney_val = df['disney_value']
            paramount_val = df['paramount_value']
            door_dash_val = df['door-dash_value']
            zoom_val = df['zoom_value']
            black_rock_val = df['black-rock_value']
            shell_val = df['shell_value']
            general_electric_val = df['general-electric_value']
            phizer_val = df['phizer_value']
            costco_val = df['costco_value']
            boeing_val = df['boeing_value']
            target_val = df['target_value']

            fig, ax = plt.subplots()

            l1, = ax.plot(time, apple_val)
            l2, = ax.plot(time, microsoft_val)
            l3, = ax.plot(time, walmart_val)
            l4, = ax.plot(time, mcdonalds_val)
            l5, = ax.plot(time, tesla_val)
            l6, = ax.plot(time, meta_val)
            l7, = ax.plot(time, bilibili_val)
            l8, = ax.plot(time, intel_val)
            l9, = ax.plot(time, amazon_val)
            l10, = ax.plot(time, nvidia_val)
            l11, = ax.plot(time, IBM_val)
            l12, = ax.plot(time, shopify_val)
            l13, = ax.plot(time, telus_val)
            l14, = ax.plot(time, honda_val)
            l15, = ax.plot(time, general_motors_val)
            l16, = ax.plot(time, toyota_val)
            l17, = ax.plot(time, ford_val)
            l18, = ax.plot(time, sony_val)
            l19, = ax.plot(time, dell_val)
            l20, = ax.plot(time, netflix_val)
            l21, = ax.plot(time, alphabet_val)
            l22, = ax.plot(time, spotify_val)
            l23, = ax.plot(time, disney_val)
            l24, = ax.plot(time, paramount_val)
            l25, = ax.plot(time, door_dash_val)
            l26, = ax.plot(time, zoom_val)
            l27, = ax.plot(time, black_rock_val)
            l28, = ax.plot(time, shell_val)
            l29, = ax.plot(time, general_electric_val)
            l30, = ax.plot(time, phizer_val)
            l31, = ax.plot(time, costco_val)
            l32, = ax.plot(time, boeing_val)
            l33, = ax.plot(time, target_val)


            lines = (l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l30, l31, l32, l33)
            choices_plotted = ('apple', 'microsoft', 'walmart', 'mcdonalds', 'tesla', 'meta', 'bilibili', 'intel', 'amazon', 'nvidia', 'IBM', 'shopify', 'telus', 'honda', 'general motors', 'toyota', 'ford', 'sony', 'dell', 'netflix', 'alphabet', 'spotify', 'disney', 'paramount', 'door dash', 'zoom', 'black rock', 'shell', 'general electric', 'phizer', 'costco', 'boeing', 'target')
            check_state = (True, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False)

        elif type == 'currency':
            df = pd.read_csv('pre-plotted_graphs/markets/currency.csv', index_col='time')
            times = df.index
            USD = df['us_dollar_val']
            CAD = df['Canadian_dollar_val']
            euro = df['euro_val']
            yen = df['yen_val']
            peso = df['peso_val']
            pound = df['pound_val']

            l1, = ax.plot(times, USD)
            l2, = ax.plot(times, CAD)
            l3, = ax.plot(times, euro)
            l4, = ax.plot(times, yen)
            l5, = ax.plot(times, peso)
            lines = (l1, l2, l3, l4, l5)

            choice_plotted = ('USD', 'CAD', 'euro', 'yen', 'peso')
            check_state = (True, False, False, False, False)

        elif type == 'crypto':
            df = pd.read_csv('pre_ploted_graphs/markets/crypto.csv', index_col='time')
            times = df.index
            bitcoin = df['bitcoin_val']
            dogecoin = df['dogecoin_val']
            ethereum = df['ethereum_val']
            tether = df['tether_val']
            solana = df['solana_val']

            l1, = ax.plot(times, bitcoin)
            l2, = ax.plot(times, dogecoin)
            l3, = ax.plot(times, ethereum)
            l4, = ax.plot(times, tether)
            l5, = ax.plot(times, solana)
            lines = (l1, l2, l3, l4, l5)

            choices_plotted = ('bitcoin', 'dogecoin', 'ethereum', 'tether', 'solana')
            check_state = (True, False, False, False, False)
    def setVisible(label_name):
        option_indx = choices_plotted.index(label_name)
        line = lines[option_indx]
        line.set_visible(not line.get_visible())
        plt.draw()
    ax_checkbox = plt.axes([0.0, 0.0, 0.12, 0.9])
    checkbox = CheckButtons(ax_checkbox, choices_plotted, check_state)
    checkbox.on_clicked(setVisible)
    for i, line in enumerate(lines):
        line.set_visible(check_state[i])
    ax_checkbox = plt.axes([0.0, 0.0, 0.12, 0.009])
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
elif types == '12':
    a = input("a: ")
    b = input("b: ")
    c = input("c: ")
    x1 = -int(b) + math.sqrt(int(b)**2 - 4*(int(a)*int(c)))/2*int(a)
    x2 = -int(-b) - math.sqrt(int(b)**2 - 4*(int(a)*int(c)))/2*int(a)
    print("\n", x1 + x2)
plt.grid(True)
plt.show()
