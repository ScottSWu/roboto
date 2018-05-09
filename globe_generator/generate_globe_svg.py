import math
import numpy

REAL_WIDTH = 3.6 * 2.0 * math.pi
REAL_HEIGHT = 3.6 * math.pi
WIDTH=2048
HEIGHT=1024
SLICES = 8
RESOLUTION = 1 # degrees

if __name__ == "__main__":
  SLICE_WIDTH = WIDTH / SLICES
  f = open("globe.svg", "w")
  f.write("<svg xmlns=\"http://www.w3.org/2000/svg\" xmlns:x=\"http://www.w3.org/1999/xlink\" width=\"{}in\" height=\"{}in\" viewBox=\"0 0 {} {}\">\n".format(REAL_WIDTH, REAL_HEIGHT, WIDTH, HEIGHT))
  
  f.write("<defs>\n")
  f.write("<g>\n")
  
  points = []
  for l in numpy.linspace(0, 1, 360 / RESOLUTION):
    w = SLICE_WIDTH * math.sin(l * math.pi)
    x = SLICE_WIDTH / 2.0 - w / 2.0
    y = l * HEIGHT
    points.append("{},{}".format(x, y))
  
  for l in numpy.linspace(1, 0, 360 / RESOLUTION):
    w = SLICE_WIDTH * math.sin(l * math.pi)
    x = SLICE_WIDTH / 2.0 + w / 2.0
    y = l * HEIGHT
    points.append("{},{}".format(x, y))
  
  f.write("<polyline id=\"strip\" points=\"{}\" fill=\"none\" stroke=\"black\" />\n".format(" ".join(points)))
  f.write("</g>\n")
  f.write("</defs>\n")
  
  for i in range(SLICES):
    f.write("<use href=\"#strip\" x=\"{}\" y=\"0\" />\n".format(SLICE_WIDTH * i))
  
  
  f.write("</svg>\n")
  f.close()
