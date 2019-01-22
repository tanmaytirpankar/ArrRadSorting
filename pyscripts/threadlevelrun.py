import subprocess
import sys
logfile = open('logfile','w')
obj = [{"numpoints" : 1000, "numthreads" : 2, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 4, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 8, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 12, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 16, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 20, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 24, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 28, "wordsize" : 2, "levels" : 8},
       {"numpoints" : 1000, "numthreads" : 32, "wordsize" : 2, "levels" : 8},
]
for pars in obj:
    subprocess.call(["../cmake-build-debug/ArrRadSorting", "-p", str(pars["numpoints"]), "-t", str(pars["numthreads"]), "-w", str(pars["wordsize"]), "-l", str(pars["levels"])],stdout=logfile, stderr=logfile)
