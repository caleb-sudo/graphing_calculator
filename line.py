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
    elif gr == '1':
        type = input("type: ")
        if type == '1':
            df = pd.read_csv('pre-plotted_graphs/markets/resources.csv', index_col='time(month/day/year)')
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
            times = df.index

            apple = df['apple']
            microsoft = df['microsoft']
            walmart = df['walmart']
            mcdonalds = df['mcdonalds']
            tesla = df['tesla']
            meta = df['meta']
            tencent = df['tencent']
            intel = df['intel']
            amazon = df['amazon']
            nivida = df['nivida']
            IBM = df['IBM']
            samsung = df['samsung']
            telus = df['telus']
            rogers = df['rogers']
            bell = df['bell']
            toyota = df['toyota']
            ford = df['ford']
            alphabet = df['alphabet']

            fig, ax = plt.subplots()

            l1, = ax.plot(times, alphabet)
            l2, = ax.plot(times, apple)
            l3, = ax.plot(times, microsoft)
            l4, = ax.plot(times, walmart)
            l5, = ax.plot(times, mcdonalds)
            l6, = ax.plot(times, tesla)
            l7, = ax.plot(times, meta)
            l8, = ax.plot(times, tencent)
            l9, = ax.plot(times, intel)
            l10, = ax.plot(times, amazon)
            l11, = ax.plot(times, nivida)
            l12, = ax.plot(times, IBM)
            l13, = ax.plot(times, samsung)
            l14, = ax.plot(times, telus)
            l15, = ax.plot(times, rogers)
            l16, = ax.plot(times, bell)
            l17, = ax.plot(times, toyota)
            l18, = ax.plot(times, ford)

            lines = (l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18)
            choices_plotted = ('alphabet', 'apple', 'microsoft', 'walmart', 'mcdonalds', 'tesla', 'meta', 'tencent', 'intel', 'amazon', 'nivida', 'IBM', 'samsung', 'telus', 'rogers', 'bell', 'toyota', 'ford')
            check_state = (True, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False)

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

            choice_plotted = (USD, CAD, euro, yen, peso)
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
        elif type == 'gdp':
            df = pd.read_csv('pre_plotted_graphs/markets/GDP.csv', index_col='time')
            time = df.index
            USA_gdp = df['USA_GDP']
            Canada_gdp = df['Canada_GDP']
            China_gdp = df['China_GDP']
            UK_gdp = df['UK_GDP']
            Mexico_gdp = df['Mexico_GDP']
            Japan_gdp = df['Japan_GDP']
            Peru_gdp = df['Peru_GDP']
            India_gdp = df['India_GDP']
            Russia_gdp = df['Russia_GDP']
            Germany_gdp = df['Germany_GDP']
            Italy_gdp = df['Italy_GDP']
            Norway_gdp = df['Norway_GDP']
            Poland_gdp = df['Poland_GDP']
            Panama_gdp = df['Panama_GDP']
            Finland_gdp = df['Finland_GDP']
            France_gdp = df['France_GDP']
            Brazil_gdp = df['Brazil_GDP']
            Austraila_gdp = df['Australia_GDP']
            Ukraina_gdp = df['Ukraine_GDP']
            Turkey_gdp = df['Turkey_GDP']
            Hungary_gdp = df['Hungary_GDP']
            South_Korea_gdp = df['south-korea_GDP']
            Libera_gdp = df['Libera_GDP']
            Indonisea_gdp = df['Indonisea_GDP']

            fig, ax = plt.subplots()
            
            l0, = ax.plot(time, USA_gdp)
            l1, = ax.plot(time, Canada_gdp)
            l2, = ax.plot(time, China_gdp)
            l3, = ax.plot(time, Uk_gdp)
            l4, = ax.plot(time, Mexico_gdp)
            l5, = ax.plot(time, Japan_gdp)
            l6, = ax.plot(time, Peru_gdp)
            l7, = ax.plot(time, India_gdp)
            l8, = ax.plot(time, Russia_gdp)
            l9, = ax.plot(time, Germany_gdp)
            l10, = ax.plot(time, Italy_gdp)
            l11, = ax.plot(time, Norway_gdp)
            l12, = ax.plot(time, Poland_gdp)
            l13, = ax.plot(time, Panama_gdp)
            l14, = ax.plot(times, Finland_gdp)
            l15, = ax.plot(time Frane_gdp)
            l16, = ax.plot(time, Brazil_gdp)
            l17, = ax.plot(time, Australia_gdp)
            l18, = ax.plot(time, Ukraine_gdp)
            l19, = ax.plot(time Turkey_gdp)
            l20, = ax.plot(time, Hungary_gdp)
            l21, = ax.plot(time, South_Korea_gdp)
            l22, = ax.plot(time, Libera_gdp)
            l23, = ax.plot(time, Indonisea_gdp)
            lines = (l0, l1, l2, l3, l4, l5, l6, l7, l8, l9, l10, l11, l12, l13, l14, l15, l16, l17, l18, l19, l20, l21, l22, l23)

            choices_plotted = ('USA GDP', 'Canada GDP', 'China GDP', 'UK GDP', 'Mexico GDP', 'Japan GDP', 'Peru GDP', 'India GDP', 'Russia GDP', 'Germany GDP', 'Italy GDP', 'Norway GDP', 'Poland GDP', 'Panama GDP', 'Finland GDP', 'France GDP', 'Brazil GDP', 'Austraila GDP', 'Ukraine GDP', 'Turkey GDP', 'Hungary GDP', 'South Korea GDP', 'Libera GDP', 'Indonisea GDP') 
            check_state = (True, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False, False)
'21    def setVisible(label_name):
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
