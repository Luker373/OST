# USEAGE: python gnost_to_matlab.py [-k,c] [files...]
# -k: create kml file from data
# -c: create raw coords file from data

import sys
import math
from decimal import Decimal, DecimalException

def gps_lat_handle(x):
    y = x - 1
    while gps_lat_arr[y] == 0:
        y = y - 1
    print('gps_lat_arr[%d]: REPLACED %f WITH: %f' % (x, gps_lat_arr[x], gps_lat_arr[y]))
    gps_lat_arr[x] = gps_lat_arr[y]

def gps_long_handle(x):
    y = x - 1
    while gps_long_arr[y] == 0:
        y = y - 1
    print('gps_long_arr[%d]: REPLACED %f WITH: %f' % (x, gps_long_arr[x], gps_long_arr[y]))
    gps_long_arr[x] = gps_long_arr[y]

def wind_s_handle(x):
    y = x - 1
    while wind_s_arr[y] == 0:
        y = y - 1
    print('wind_s_arr[%d]: REPLACED %f WITH: %f' % (x, wind_s_arr[x], wind_s_arr[y]))
    wind_s_arr[x] = wind_s_arr[y]

def wind_d_handle(x):
    y = x - 1
    while wind_d_arr[y] == 0:
        y = y - 1
    print('wind_d_arr[%d]: REPLACED %f WITH: %f' % (x, wind_d_arr[x], wind_d_arr[y]))
    wind_d_arr[x] = wind_d_arr[y]

def boat_s_handle(x):
    y = x - 1
    while boat_s_arr[y] == 0:
        y = y - 1
    print('boat_s_arr[%d]: REPLACED %f WITH: %f' % (x, boat_s_arr[x], boat_s_arr[y]))
    boat_s_arr[x] = boat_s_arr[y]

def boat_d_handle(x):
    y = x - 1
    while boat_d_arr[y] == 0:
        y = y - 1
    print('boat_d_arr[%d]: REPLACED %f WITH: %f' % (x, boat_d_arr[x], boat_d_arr[y]))
    boat_d_arr[x] = boat_d_arr[y]

def boom_ang_handle(x):
    y = x - 1
    while boom_ang_arr[y] == 0:
        y = y - 1
    print('boom_ang_arr[%d]: REPLACED %f WITH: %f' % (x, boom_ang_arr[x], boom_ang_arr[y]))
    boom_ang_arr[x] = boom_ang_arr[y]

def compass_handle(x):
    y = x - 1
    while compass_arr[y] == 0:
        y = y - 1
    print('compass_arr[%d]: REPLACED %f WITH: %f' % (x, compass_arr[x], compass_arr[y]))
    compass_arr[x] = compass_arr[y]

def timestamp_handle(x):
    y = x - 1
    while timstamp_arr[y] == 0:
        y = y - 1
    print('timstamp_arr[%d]: REPLACED %f WITH: %f' % (x, timstamp_arr[x], timstamp_arr[y]))
    timstamp_arr[x] = timstamp_arr[y]

excpt_dict = {  0: gps_lat_handle,
                1: gps_long_handle,
                2: wind_s_handle,
                3: wind_d_handle,
                4: boat_s_handle,
                5: boat_d_handle,
                6: boom_ang_handle,
                7: compass_handle,
                8: timestamp_handle,
            }

kml_out = 0
coord_out = 0
for j in range(1, len(sys.argv)):
    if sys.argv[j] == "-k":
        kml_out = 1
        continue
    if sys.argv[j] == "-c":
        coord_out = 1
        continue
    f = open(sys.argv[j])
    print("Opened argv number", j, sys.argv[j])

    for i, l in enumerate(f):
        pass
    f = open(sys.argv[j])

    boat_s_arr = [0] * (i + 1)
    boat_d_arr = [0] * (i + 1)
    wind_s_arr = [0] * (i + 1)
    wind_d_arr = [0] * (i + 1)
    timstamp_arr = [0] * (i + 1)
    boom_ang_arr = [0] * (i + 1)
    compass_arr = [0] * (i + 1)
    gps_lat_arr = [0] * (i + 1)
    gps_long_arr = [0] * (i + 1)

    lineDict = {}

    idx = 0
    for line in f:
        line = line.translate({ord(c): None for c in '\''})
        lineDict[idx] = line.split(",")

        q = 0
        try:
            gps_lat_arr[idx] = Decimal(lineDict[idx][2])
            q = q + 1
            gps_long_arr[idx] = Decimal(lineDict[idx][3])
            q = q + 1
            wind_s_arr[idx] = Decimal(lineDict[idx][4])
            q = q + 1
            wind_d_arr[idx] = Decimal(lineDict[idx][5])
            q = q + 1
            boat_s_arr[idx] = Decimal(lineDict[idx][6])
            q = q + 1
            boat_d_arr[idx] = Decimal(lineDict[idx][7])
            q = q + 1
            boom_ang_arr[idx] = Decimal(lineDict[idx][8])
            q = q + 1
            compass_arr[idx] = Decimal(lineDict[idx][9])
            q = q + 1
            timstamp_arr[idx] = Decimal(lineDict[idx][10].split("*")[0])
        except DecimalException as e:
            excpt_dict[q](x)
            continue
        idx = idx + 1

    f.close()

    # ---------------ERRORS EXIST HERE----------------
    for x in range(0, len(gps_lat_arr)):
        if (Decimal(gps_lat_arr[x]) < 36) or (Decimal(gps_lat_arr[x]) > 37):
            gps_lat_handle(x)
    for x in range(0, len(gps_long_arr)):
        if gps_long_arr[x] > -122:
            gps_long_handle(x)

    # convert from deg-minutes-seconds to decimal degrees
    for x in range(0, len(gps_lat_arr)):
        k = Decimal(gps_lat_arr[x])
        deg = math.floor(k)
        mins = math.floor((k-deg)*100)
        secs = math.floor((k-deg)*10000-mins*100)
        k = deg + (mins/60) + (secs/3600)
        gps_lat_arr[x] = k

    for x in range(0, len(gps_long_arr)):
        k = Decimal(gps_long_arr[x])
        deg = math.ceil(k)
        mins = math.ceil((k-deg)*100)
        secs = math.ceil((k-deg)*10000-mins*100)
        k = deg + (mins/60) + (secs/3600)
        gps_long_arr[x] = k

    path = "matparse_" + sys.argv[j]
    f = open(path, "w+")

    f.write("\n%s = [" % "boatSpeed")
    for i in range(0,len(boat_s_arr)):
        f.write("%s\n" % (boat_s_arr[i]))

    f.write("];\n%s = [" % "track")
    for i in range(0,len(boat_d_arr)):
        f.write("%s\n" % (boat_d_arr[i]))

    f.write("];\n%s = [" % "windSpeed")
    for i in range(0,len(wind_s_arr)):
        f.write("%s\n" % (wind_s_arr[i]))

    f.write("];\n%s = [" % "windDeg")
    for i in range(0,len(wind_d_arr)):
        f.write("%s\n" % (wind_d_arr[i]))

    f.write("];\n%s = [" % "ts_gnost")
    for i in range(0,len(timstamp_arr)):
        f.write("%s\n" % (timstamp_arr[i]))

    f.write("];\n%s = [" % "compass_deg")
    for i in range(0,len(compass_arr)):
        f.write("%s\n" % (compass_arr[i]))

    f.write("];")
    f.close()

    if coord_out == 1:
        path = "coords_" + sys.argv[j]
        f = open(path, "w+")
        for x in range(min(len(gps_long_arr), len(gps_lat_arr))):
            f.write("%s,%s\n" % (gps_lat_arr[x], gps_long_arr[x]))
        f.close()

    if kml_out == 1:
        path = "kml_" + sys.argv[j]
        f = open(path, "w+")
        # KML file format
        f.write("<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n")
        f.write("<kml xmlns=\"http://www.opengis.net/kml/2.2\">\n")
        f.write("\t<Document>\n")
        f.write("\t\t<name>Paths</name>\n")
        f.write("\t\t<Style id=\"yellowLineGreenPoly\">\n")
        f.write("\t\t\t<LineStyle>\n")
        f.write("\t\t\t\t<color>7f00ffff</color>\n")
        f.write("\t\t\t\t<width>4</width>\n")
        f.write("\t\t\t</LineStyle>\n")
        f.write("\t\t\t<PolyStyle>\n")
        f.write("\t\t\t\t<color>7f00ff00</color>\n")
        f.write("\t\t\t</PolyStyle>\n")
        f.write("\t\t</Style>\n")
        f.write("\t\t<Placemark>\n")
        f.write("\t\t\t<name>%s</name>\n" % (sys.argv[j]))
        f.write("\t\t\t<styleUrl>#yellowLineGreenPoly</styleUrl>\n")
        f.write("\t\t\t<LineString>\n")
        f.write("\t\t\t\t<extrude>1</extrude>\n")
        f.write("\t\t\t\t<tessellate>1</tessellate>\n")
        f.write("\t\t\t\t<altitudeMode>absolute</altitudeMode>\n")
        f.write("\t\t\t\t<coordinates>\n")

        for x in range(min(len(gps_long_arr), len(gps_lat_arr))):
            f.write("\t\t\t\t\t%s,%s, 500\n" % (gps_long_arr[x], gps_lat_arr[x]))

        f.write("\t\t\t\t</coordinates>\n")
        f.write("\t\t\t</LineString>\n")
        f.write("\t\t</Placemark>\n")
        f.write("\t</Document>\n")
        f.write("</kml>\n")

        f.close()

