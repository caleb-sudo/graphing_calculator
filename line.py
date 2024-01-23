import matplotlib.pyplot as plt
import numpy as np

from matplotlib.widgets import RadioButtons, Cursor
from matplotlib.backend_bases import MouseEvent

a = np.arange(0.0, 2.0, 0.01)
x = np.linspace(-30, 30, 200, 200)
y = 2*x + 2

fig, ax = plt.subplot_mosaic(
    [
        ['main', 'color'],
    ],
    width_ratios=[5, 1],
    layout='constrained',
)
line, = ax['main'].plot(a, y, 'o')

radio_background = 'lightgoldenrodyellow'

ax['color'].set_facecolor(radio_background)
radio1 = RadioButtons(
    ax['color'], ('red', 'blue', 'green', 'black'),
    label_props={'color': ['red', 'blue', 'green', 'black']},
    radio_props={
        'facecolor': ['red', 'blue', 'green', 'black'],
        'edgecolor': ['darkred', 'darkblue', 'darkgreen', 'black'],
    }
)

def colorfunc(label):
    line.set_color(label)
    fig.canvas.draw()
radio1.on_clicked(colorfunc)

class SnappingCursor:
    def __init__(self, ax, line):
        self.ax = ax
        self.horizontal_line = ax.axhline(color='k', lw=0.8, ls='--')
        self.vertical_line = ax.axvline(color='k', lw=0.8, ls='--')
        self.text = ax.text(0.72, 0.9, '', transform=ax.transAxes)

    def set_cross_hair_visible(self, visible):
        need_redraw = self.horizontal_line.get_visible() != visible
        self.horizontal_line.set_visible(visible)
        self.vertical_line.set_visible(visible)
        self.text.set_visible(visible)
        return need_redraw

    def on_mouse_move(self, event):
        if not event.inaxes:
            need_redraw = self.set_cross_hair_visible(False)
            if need_redraw:
                self.ax.figure.canvas.draw()
        else:
            self.set_cross_hair_visible(True)
            self.horizontal_line.set_ydata([y])
            self.vertical_line.set_xdata([x])
            self.text.set_text(f'x={x:1.2f}, y={y:1.2f}')
            self.ax.figure.canvas.draw()

snap_cursor = SnappingCursor(ax, line)
fig.canvas.mpl_connect('motion_notify_event', snap_cursor.on_mouse_move)
t = ax.transData
MouseEvent(
    "motion_notify_event", ax.figure.canvas, *t.transform((0.5, 0.5))
)._process()

plt.grid(True)
plt.show()