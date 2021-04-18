import pandas as pd
import sys
import datetime 

# date range
start_year = 2012
start = datetime.datetime(start_year, 1, 1)
gen = ((start + i * datetime.timedelta(minutes=5)).strftime("%Y-%m-%d %H:%M:%S") for i in range(int(12*24*365.25*4)))
timestamps = pd.DataFrame(gen, columns=["timestamp"])
# load dataset and merge
df = pd.read_csv("101-Site_DKA-WeatherStation.csv")
df.drop(['Wind_Direction', 'Wind_Speed'], axis=1, inplace=True)
station = pd.read_csv(sys.argv[1])
station = station[["timestamp", "Active_Power"]]
df = timestamps.merge(df, on="timestamp", how='outer')
df = df.merge(station, on="timestamp", how='outer')
df = df[(df['timestamp'].str.slice(0, 4) >= str(start_year)) 
        & (df['timestamp'].str.slice(0, 4) < str(start_year + 4))]
# feature engineering
date_time = pd.to_datetime(df.pop('timestamp'), format='%Y-%m-%d %H:%M:%S')
df["Weather_Temperature_Kelvin"] = df.pop("Weather_Temperature_Celsius").apply(lambda c: c + 273.15)
df = df.mask(df < 0)
df = df.mask((df < df.quantile(0.05)) | (df > df.quantile(0.95)))
df = df.interpolate(method='linear', axis=0).ffill().bfill()

assert(len(df) == len(timestamps))              
df.to_csv(f"{sys.argv[1]}_merged.csv.zip", index=False, compression='zip')