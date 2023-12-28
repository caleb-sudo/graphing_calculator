import plotly.express as px
import ctypes
graph = ctype.CDLL("lib/graph.dll")
slope = ctype.c_int.in_dll(graph, "slope")
x_int = ctype.c_int.in_dll(graph, "x_intercept")
y_int = ctype.c_int.in_dll(graph, "y_intercept")
fig = px.scatter_3d(graph, x, y, z)
fig.show()
