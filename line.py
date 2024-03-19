import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import geopandas as gpd
import folium
import geodatasets
import contextily as cx
import math

from menus import menu
from textbox import *

from mpl_toolkits.axes_grid1 import host_subplot
from matplotlib.widgets import RadioButtons, Cursor, CheckButtons 
from matplotlib.backend_bases import MouseEvent, MouseButton

ax = plt.subplots()
a = np.arange(0.0, 2.0, 0.01)
c1 = "1: slope intercept form\n"
c2 = "2: general form\n"
c3 = "3: point-slope form NA\n"
c4 = "4: pie chart NA\n"
c5 = "5: scattered plot NA\n"
c6 = "6: bar chart NA\n"
c7 = "7: 3d chart NA\n"
c8 = "8: histogram chart NA\n"
c9 = "9: pre-plotted graphs\n"
c10 = "10: vertex form\n"
c11 = "11: standard form\n"
c12 = "12: point chart\n"
c13 = "13: quadradic inequalities\n"
c14 = "14: linear inequalities\n"

print("\n",c1 + c2 + c3 + c4 + c5 + c6 + c7 + c8 + c9 + c10 + c11 + c12 + c13 + c14)

types = input("graph: ")

if types == '1' or types == 'slope-intercept form':
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

elif types == '9' or types == 'pre-plotted data':
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

            type = input("type: ")

            if type == 'val':
                from val import *

            elif type == 'vol':
                from vol import *

            fig, ax = plt.subplots()

            l1, = ax.plot(time, apple)
            l2, = ax.plot(time, microsoft)
            l3, = ax.plot(time, walmart)
            l4, = ax.plot(time, mcdonalds)
            l5, = ax.plot(time, tesla)
            l6, = ax.plot(time, meta)
            l7, = ax.plot(time, bilibili)
            l8, = ax.plot(time, intel)
            l9, = ax.plot(time, amazon)
            l10, = ax.plot(time, nvidia)
            l11, = ax.plot(time, IBM)
            l12, = ax.plot(time, shopify)
            l13, = ax.plot(time, telus)
            l14, = ax.plot(time, honda)
            l15, = ax.plot(time, general_motors)
            l16, = ax.plot(time, toyota)
            l17, = ax.plot(time, ford)
            l18, = ax.plot(time, sony)
            l19, = ax.plot(time, dell)
            l20, = ax.plot(time, netflix)
            l21, = ax.plot(time, alphabet)
            l22, = ax.plot(time, spotify)
            l23, = ax.plot(time, disney)
            l24, = ax.plot(time, paramount)
            l25, = ax.plot(time, door_dash)
            l26, = ax.plot(time, zoom)
            l27, = ax.plot(time, black_rock)
            l28, = ax.plot(time, shell)
            l29, = ax.plot(time, general_electric)
            l30, = ax.plot(time, phizer)
            l31, = ax.plot(time, costco)
            l32, = ax.plot(time, boeing)
            l33, = ax.plot(time, target)
            l34, = ax.plot(time, snap)
            l35, = ax.plot(time, pintrest)
            l36, = ax.plot(time, warner)
            l37, = ax.plot(time, best_buy)
            l38, = ax.plot(time, cloudflare)
            l39, = ax.plot(time, datadog)
            l40, = ax.plot(time, crowdstrike)
            l41, = ax.plot(time, snowflake)
            l42, = ax.plot(time, gitlab)
            l43, = ax.plot(time, zscaler)
            l44, = ax.plot(time, fastly)
            l45, = ax.plot(time, okta)
            l46, = ax.plot(time, duolingo)
            l47, = ax.plot(time, nike)
            l48, = ax.plot(time, visa)
            l49, = ax.plot(time, mastercard)
            l50, = ax.plot(time, paypal)
            l52, = ax.plot(time, saleforce)
            l51, = ax.plot(time, american_express)
            l52, = ax.plot(time, adobe)
            l53, = ax.plot(time, caterpiller)
            l54, = ax.plot(time, servicenow)
            l55, = ax.plot(time, workday)
            l56, = ax.plot(time, autodesk)
            l57, = ax.plot(time, atlassian)
            l58, = ax.plot(time, hasbro)
            l59, = ax.plot(time, mattel)
            l60, = ax.plot(time, bp)
            l61, = ax.plot(time, exxon)
            l62, = ax.plot(time, j_and_j)
            l63, = ax.plot(time, chevron)
            l64, = ax.plot(time, suncor)
            l65, = ax.plot(time, amgen)
            l66, = ax.plot(time, biogen)
            l67, = ax.plot(time, regeneron)
            l68, = ax.plot(time, vertex)
            l69, = ax.plot(time, madrigal)
            l70, = ax.plot(time, biomarin)
            l71, = ax.plot(time, incyte)
            l72, = ax.plot(time, exelixis)
            l73, = ax.plot(time, nyt)


            lines = (l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21, l22, l23, l24, l25, l26, l27, l28, l29, l30, l31, l32, 
                     l33, l34, l35, l36, l37, l38, l39, l40, l41, l42, l43, l44, l45, l46, l47, l48, l49, l50, l51, l52, l53, l54, l55, l56, l57, l58, l59, l60, l61, l62,
                    l63, l64, l65, l66, l67, l68, l69, l70, l71, l72, l73)
            choices_plotted = ('apple', 'microsoft', 'walmart', 'mcdonalds', 'tesla', 'meta', 'bilibili', 'intel', 'amazon', 'nvidia', 'IBM', 'shopify', 'telus', 'honda', 
                               'general motors', 'toyota', 'ford', 'sony', 'dell', 'netflix', 'alphabet', 'spotify', 'disney', 'paramount', 'door dash', 'zoom', 'black rock', 
                               'shell', 'general electric', 'phizer', 'costco', 'boeing', 'target', 'snap', 'pintrest', 'warner bros', 'best buy', 'cloudflare', 'datadog', 
                               'crowdstrike holdings', 'snowflake', 'gitlab', 'zscaler', 'fastly', 'okta', 'duolingo', 'nike', 'visa', 'mastercard', 'paypal', 'saleforce',
                                'american express', 'adobe', 'caterpiller', 'workday', 'autodesk', 'atlassian', 'hasbro', 'mattel', 'bp', 'exxon mobile',
                                'johnsen and johnsen', 'chevron', 'suncor', 'amgen', 'biogen', 'regeneron pharmaceuticals', 'vertex pharmaceuticals', 'madrigal pharmaceuticals',
                              'biomarin pharmaceuticals', 'incyte', 'exelixis', 'new york times')
            check_state = (True, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, 
                           False, False, False, False, False, False, False, False, False, False, False, False, False, False, False,False,False,False, False, False, 
                           False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False,
                           False, False, False, False, False, False, False, False, False, False, False, False, False)

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
elif types == '10' or types == 'vertex form':
    x = np.linspace(-30, 30, 300)
    a = input("a: ")
    p = input("p: ")
    q = input("q: ")
    y = int(a)*(x - int(p))**2 + int(q)
    plt.plot(x, y)
elif types == '11' or types == 'standard form':
    x = np.linspace(-30, 30, 300)
    a = input("A: ")
    b = input("B: ")
    c = input("C: ")
    y = int(a)*x**2 + int(b)*x + int(c)
    plt.plot(x, y)
elif types == '12' or 'point chart':
    xin = input("")
    yin = input("")
    xout = [xin]
    yout = [yin]
    plt.plot(xout, yout)
elif types == '13' or 'quadradic inequalities':
    print("\n")
elif types == '14' or 'linear inequalities':
    print("\n")
plt.grid(True)
plt.show()
