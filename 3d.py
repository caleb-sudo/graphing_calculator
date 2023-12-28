import plotly.express as px
import ctypes
graph = ctypes.CDLL("lib/graph.dll")
x = ctypes.c_int.in_dll(graph, "x")
y = ctypes.c_int.in_dll(graph, "y")
z = ctypes.c_int.in_dll(graph, "z")
fig = px.scatter_3d(graph, x, y, z)
fig.show()
