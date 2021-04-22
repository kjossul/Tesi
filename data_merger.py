import pandas as pd
import numpy as np
import sys
import datetime 

# date range
start_year = 2014
years_in_dataset = 4
def open_csv():
    start = datetime.datetime(start_year, 1, 1)
    gen = ((start + i * datetime.timedelta(minutes=5)).strftime("%Y-%m-%d %H:%M:%S") for i in range(int(12*24*365.25*years_in_dataset)))
    timestamps = pd.DataFrame(gen, columns=["timestamp"])
    # load dataset and merge
    df = pd.read_csv("101-Site_DKA-WeatherStation.csv")
    df.drop(['Wind_Direction', 'Wind_Speed', 'Radiation_Global_Tilted', 'Radiation_Diffuse_Tilted'], axis=1, inplace=True)
    station = pd.read_csv(sys.argv[1])
    station = station[["timestamp", "Active_Power"]]
    df = timestamps.merge(df, on="timestamp", how='outer')
    df = df.merge(station, on="timestamp", how='outer')
    df = df[(df['timestamp'].str.slice(0, 4) >= str(start_year)) 
            & (df['timestamp'].str.slice(0, 4) < str(start_year + 4))]
    return df
    
def drop_problematic_days(df, threshold=10):
    total_days = len(df) / (12 * 24)
    # keeps only days where at least threshold days are not null
    filtered = [chunk for chunk in np.array_split(df, total_days) if chunk.shape[0] - chunk.dropna().shape[0] < threshold]
    return pd.DataFrame(np.concatenate(filtered), columns=df.columns.values)

def feature_engineering(df):
    timestamps = pd.to_datetime(df.pop('timestamp'), format='%Y-%m-%d %H:%M:%S')
    df["Weather_Temperature_Kelvin"] = df.pop("Weather_Temperature_Celsius").apply(lambda c: c + 273.15)
    df = df.mask(df < 0)
    df = df.mask((df < df.quantile(0.05)) | (df > df.quantile(0.95)))
    df = df.interpolate(method='linear', axis=0).ffill().bfill()
    assert(len(df) == len(timestamps))   
    df['timestamp'] = timestamps
    return df

def save_to_csv(df):    
    df.to_csv(f"{sys.argv[1]}_merged.csv.zip", index=False, compression='zip')
    
if __name__ == '__main__':
    df = open_csv()
    df = drop_problematic_days(df)
    df = feature_engineering(df)
    save_to_csv(df)