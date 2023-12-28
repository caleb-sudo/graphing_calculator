import plotly.express as px
import ctypes
graph = ctypes.CDLL("lib/graph.dll")
x = ctypes.c_int.in_dll(graph, "x")
y = ctypes.c_int.in_dll(graph, "y")
fig = px.scatter(x = [x], y = [y]);
fig.show()
