import pandas as pd
import numpy as np
import sys
import datetime
import matplotlib.pyplot as plt
from itertools import product

class DayPair:
    """Pair of day dataframe groups"""
    COL = "101_DKA_WeatherStation_Diffuse_Horizontal_Radiation"
    
    def __init__(self, a, b):
        self.a = a
        self.b = b
        self.similarity = cosine_similarity(a[1][self.COL], b[1][self.COL])
        
    def plot(self):
        self.a[1].plot()
        self.b[1].plot()
        plt.show()
    
def read_csv(s):
    df = pd.read_csv(s)
    df['timestamp'] = df['timestamp'].apply(pd.to_datetime)
    df.set_index('timestamp', inplace=True)
    return df
    
def open_datasets(*args):
    return (read_csv(arg) for arg in args)
    
def cosine_similarity(x, y):
    return np.dot(x, y) / np.linalg.norm(x) / np.linalg.norm(y)
    
def group_days(df):
    return [group for group in df.groupby([df.index.year, df.index.month, df.index.day]) if len(group[1]) == 12 * 24]
    
def main(df_a, df_b):
    cols = ["101_DKA_WeatherStation_Diffuse_Horizontal_Radiation"] + [col for col in df_a.columns.values if 'Active_Power' in col]
    days_a, days_b = group_days(df_a[cols]), group_days(df_b[cols])
    return list(sorted((DayPair(a, b) for a, b in product(days_a, days_b)), key=lambda pair: pair.similarity, reverse=True))
    
if  __name__ == '__main__':
    df_a, df_b = open_datasets("Alice_Springs_2009.csv", "Alice_Springs_2020.csv")
    pairs = main(df_a, df_b)

