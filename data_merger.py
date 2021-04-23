import pandas as pd
import sys

# date range
start_year = 2010
training_years = 3
test_year = 2020


def read_csv(filename):
    weather = pd.read_csv("101-Site_DKA-WeatherStation.zip")
    weather.drop(['Wind_Direction', 'Wind_Speed', 'Radiation_Global_Tilted', 'Radiation_Diffuse_Tilted'], axis=1,
                 inplace=True)
    station = pd.read_csv(filename)
    station = station[["timestamp", "Active_Power"]]
    df = weather.merge(station, on="timestamp", how='outer')
    df = df[df['timestamp'].str.slice(0, 4)
        .isin([str(y) for y in range(start_year, start_year + training_years)] + [str(test_year)])]
    print("applying timestamp indexing")
    df['timestamp'] = df['timestamp'].apply(lambda s: pd.to_datetime(s, format='%Y-%m-%d %H:%M:%S'))
    df.set_index('timestamp', inplace=True)
    df.sort_index(inplace=True)
    return df


def drop_null_days(df):
    return pd.concat([group for _, group in df.groupby([df.index.year, df.index.month, df.index.day])
                      if group.dropna().shape[0] == 12 * 24])


def feature_engineering(df):
    df["Weather_Temperature_Kelvin"] = df.pop("Weather_Temperature_Celsius").apply(lambda c: c + 273.15)
    df = df.mask(df < 0)
    df = df.mask((df < df.quantile(0.05)) | (df > df.quantile(0.95)))
    df = df.interpolate(method='linear', axis=0).ffill().bfill()
    return df


def save_to_csv(df, filename):
    df.to_csv(f"{filename}_merged.csv.zip", compression='zip')


if __name__ == '__main__':
    try:
        filename = sys.argv[1]
    except IndexError:
        filename = "93-Site_8-Kaneka.zip"
    df = read_csv(filename)
    df = drop_null_days(df)
    df = feature_engineering(df)
    save_to_csv(df, filename)
