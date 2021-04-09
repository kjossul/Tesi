import pandas as pd
import sys
import datetime 
  
# date range
start = datetime.datetime(2010, 1, 1)
gen = ((start + i * datetime.timedelta(minutes=5)).strftime("%Y-%m-%d %H:%M:%S") for i in range(int(12*24*365.25*4)))
timestamps = pd.DataFrame(gen, columns=["timestamp"])
# reading csv files
wheather = pd.read_csv(sys.argv[1])
wheather = wheather[["timestamp", "Wind_Speed", "Weather_Temperature_Celsius", "Weather_Relative_Humidity", 
                    "Global_Horizontal_Radiation", "Diffuse_Horizontal_Radiation", "Wind_Direction"]]
station = pd.read_csv(sys.argv[2])
station = station[["timestamp", "Active_Power"]]
# merge dataframes
merged = pd.merge(timestamps, wheather, on='timestamp', how='outer')     
merged = pd.merge(merged, station, on='timestamp', how='outer')
merged = merged[(merged['timestamp'].str.slice(0, 4) >= '2010') & (merged['timestamp'].str.slice(0, 4) < '2014')]
assert(len(merged) == len(timestamps))              
merged.to_csv(f"{sys.argv[2]}_merged.csv.zip", index=False, compression='zip')