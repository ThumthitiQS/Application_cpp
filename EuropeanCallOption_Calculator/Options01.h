
data_monthly['ln_oil_spot_WTI'] = np.log(data_monthly['oil_spot_WTI'] +0.01 )
data_monthly['ln_oil_spot_Brent'] = np.log(data_monthly['oil_spot_Brent'])
data_monthly['ln_future_oil_contract_1'] = np.log(data_monthly['future_oil_contract_1']+0.01)
data_monthly['ln_future_oil_contract_2'] = np.log(data_monthly['future_oil_contract_2']+0.01)
data_monthly['ln_future_oil_contract_3'] = np.log(data_monthly['future_oil_contract_3']+0.01)
data_monthly['ln_future_oil_contract_4'] = np.log(data_monthly['future_oil_contract_4']+0.01)
data_monthly['ln_Gasoline_Price_US'] = np.log(data_monthly['Gasoline_Price_US']+0.01)
data_monthly['ln_Gasoline_Price_US_future'] = np.log(data_monthly['future_gasoline_US']+0.01)
data_monthly['ln_sugar_price_us'] = np.log(data_monthly['sugar_price_us']+0.01)
data_monthly['ln_ethanol_price_us'] = np.log(data_monthly['ethanol_price_us']+0.01)



data_monthly['ln_oil_spot_WTI_lag'] = data_monthly['ln_oil_spot_WTI'].shift(1)
data_monthly['ln_oil_spot_Brent_lag'] = data_monthly['ln_oil_spot_Brent'].shift(1)
data_monthly['ln_future_oil_contract_1_lag']= data_monthly['ln_future_oil_contract_1'].shift(1)
data_monthly['ln_future_oil_contract_2_lag']= data_monthly['ln_future_oil_contract_2'].shift(1)
data_monthly['ln_future_oil_contract_3_lag']= data_monthly['ln_future_oil_contract_3'].shift(1)
data_monthly['ln_future_oil_contract_4_lag']= data_monthly['ln_future_oil_contract_4'].shift(1)
data_monthly['ln_Gasoline_Price_US_lag']= data_monthly['ln_Gasoline_Price_US'].shift(1)
data_monthly['ln_Gasoline_Price_US_future_lag']= data_monthly['ln_Gasoline_Price_US_future'].shift(1)
data_monthly['ln_sugar_price_us_lag']= data_monthly['ln_sugar_price_us'].shift(1)
data_monthly['ln_ethanol_price_us_lag']= data_monthly['ln_ethanol_price_us'].shift(1)



data_monthly['chg_oil_spot_WTI'] = data_monthly['ln_oil_spot_WTI'] - data_monthly['ln_oil_spot_WTI_lag']
data_monthly['chg_oil_spot_Brent'] = data_monthly['ln_oil_spot_Brent'] - data_monthly['ln_oil_spot_Brent_lag']
data_monthly['chg_oil_future_contract1'] = data_monthly['ln_future_oil_contract_1'] - data_monthly['ln_future_oil_contract_1_lag']
data_monthly['chg_oil_future_contract2'] = data_monthly['ln_future_oil_contract_2'] - data_monthly['ln_future_oil_contract_2_lag']
data_monthly['chg_oil_future_contract3'] = data_monthly['ln_future_oil_contract_3'] - data_monthly['ln_future_oil_contract_3_lag']
data_monthly['chg_oil_future_contract4'] = data_monthly['ln_future_oil_contract_4'] - data_monthly['ln_future_oil_contract_4_lag']
data_monthly['chg_Gasoline_price_US'] = data_monthly['ln_Gasoline_Price_US'] - data_monthly['ln_Gasoline_Price_US_lag']
data_monthly['chg_future_gasoline_US'] = data_monthly['ln_Gasoline_Price_US_future'] - data_monthly['ln_Gasoline_Price_US_future_lag']
data_monthly['chg_Sugar_price_US'] = data_monthly['ln_sugar_price_us'] - data_monthly['ln_sugar_price_us_lag']
data_monthly['chg_ethanol_price_US'] = data_monthly['ln_ethanol_price_us'] - data_monthly['ln_ethanol_price_us_lag']




data_monthly['chg_oil_spot_WTI_Positive'] = np.where(data_monthly['chg_oil_spot_WTI'] >= 0 , data_monthly['chg_oil_spot_WTI'] , 0)
data_monthly['chg_oil_spot_Brent_Positive'] = np.where(data_monthly['chg_oil_spot_Brent'] >= 0 , data_monthly['chg_oil_spot_Brent'] , 0)
data_monthly['chg_oil_future_contract1_Positive'] = np.where(data_monthly['chg_oil_future_contract1'] >= 0 , data_monthly['chg_oil_future_contract1'] , 0)
data_monthly['chg_oil_future_contract2_Positive'] = np.where(data_monthly['chg_oil_future_contract2'] >= 0 , data_monthly['chg_oil_future_contract2'] , 0)
data_monthly['chg_oil_future_contract3_Positive'] = np.where(data_monthly['chg_oil_future_contract3'] >= 0 , data_monthly['chg_oil_future_contract3'] , 0)
data_monthly['chg_oil_future_contract4_Positive'] = np.where(data_monthly['chg_oil_future_contract4'] >= 0 , data_monthly['chg_oil_future_contract4'] , 0)
data_monthly['chg_Gasoline_price_US_Positive'] = np.where(data_monthly['chg_Gasoline_price_US'] >= 0 , data_monthly['chg_Gasoline_price_US'] , 0)
data_monthly['chg_future_gasoline_US_Positive'] = np.where(data_monthly['chg_future_gasoline_US'] >= 0 , data_monthly['chg_future_gasoline_US'] , 0)
data_monthly['chg_Sugar_price_US_Positive'] = np.where(data_monthly['chg_Sugar_price_US'] >= 0 , data_monthly['chg_Sugar_price_US'] , 0)
data_monthly['chg_ethanol_price_US_Positive'] = np.where(data_monthly['chg_ethanol_price_US'] >= 0 , data_monthly['chg_ethanol_price_US'] , 0)






data_monthly['chg_oil_spot_WTI_Negative'] = np.where(data_monthly['chg_oil_spot_WTI'] < 0 , data_monthly['chg_oil_spot_WTI'] , 0)
data_monthly['chg_oil_spot_Brent_Negative'] = np.where(data_monthly['chg_oil_spot_Brent'] < 0 , data_monthly['chg_oil_spot_Brent'] , 0)
data_monthly['chg_oil_future_contract1_Negative'] = np.where(data_monthly['chg_oil_future_contract1'] < 0 , data_monthly['chg_oil_future_contract1'] , 0)
data_monthly['chg_oil_future_contract2_Negative'] = np.where(data_monthly['chg_oil_future_contract2'] < 0 , data_monthly['chg_oil_future_contract2'] , 0)
data_monthly['chg_oil_future_contract3_Negative'] = np.where(data_monthly['chg_oil_future_contract3'] < 0 , data_monthly['chg_oil_future_contract3'] , 0)
data_monthly['chg_oil_future_contract4_Negative'] = np.where(data_monthly['chg_oil_future_contract4'] < 0 , data_monthly['chg_oil_future_contract4'] , 0)
data_monthly['chg_Gasoline_price_US_Negative'] = np.where(data_monthly['chg_Gasoline_price_US'] < 0 , data_monthly['chg_Gasoline_price_US'] , 0)
data_monthly['chg_future_gasoline_US_Negative'] = np.where(data_monthly['chg_future_gasoline_US'] < 0 , data_monthly['chg_future_gasoline_US'] , 0)
data_monthly['chg_Sugar_price_US_Negative'] = np.where(data_monthly['chg_Sugar_price_US'] < 0 , data_monthly['chg_Sugar_price_US'] , 0)
data_monthly['chg_ethanol_price_US_Negative'] = np.where(data_monthly['chg_ethanol_price_US'] < 0 , data_monthly['chg_ethanol_price_US'] , 0)







data_monthly['chg_oil_future_contract1_Positive_lag1'] = data_monthly['chg_oil_future_contract1_Positive'].shift(1)
data_monthly['chg_oil_future_contract1_Positive_lag2'] = data_monthly['chg_oil_future_contract1_Positive'].shift(2)
data_monthly['chg_oil_future_contract1_Positive_lag3'] = data_monthly['chg_oil_future_contract1_Positive'].shift(3)
data_monthly['chg_oil_future_contract1_Positive_lag4'] = data_monthly['chg_oil_future_contract1_Positive'].shift(4)
data_monthly['chg_oil_future_contract1_Positive_lag5'] = data_monthly['chg_oil_future_contract1_Positive'].shift(5)
data_monthly['chg_oil_future_contract1_Positive_lag6'] = data_monthly['chg_oil_future_contract1_Positive'].shift(6)


data_monthly['chg_oil_future_contract1_Negative_lag1'] = data_monthly['chg_oil_future_contract1_Negative'].shift(1)
data_monthly['chg_oil_future_contract1_Negative_lag2'] = data_monthly['chg_oil_future_contract1_Negative'].shift(2)
data_monthly['chg_oil_future_contract1_Negative_lag3'] = data_monthly['chg_oil_future_contract1_Negative'].shift(3)
data_monthly['chg_oil_future_contract1_Negative_lag4'] = data_monthly['chg_oil_future_contract1_Negative'].shift(4)
data_monthly['chg_oil_future_contract1_Negative_lag5'] = data_monthly['chg_oil_future_contract1_Negative'].shift(5)
data_monthly['chg_oil_future_contract1_Negative_lag6'] = data_monthly['chg_oil_future_contract1_Negative'].shift(6)


data_monthly['chg_oil_spot_WTI_Positive_lag1'] = data_monthly['chg_oil_spot_WTI_Positive'].shift(1)
data_monthly['chg_oil_spot_WTI_Positive_lag2'] = data_monthly['chg_oil_spot_WTI_Positive'].shift(2)
data_monthly['chg_oil_spot_WTI_Positive_lag3'] = data_monthly['chg_oil_spot_WTI_Positive'].shift(3)
data_monthly['chg_oil_spot_WTI_Positive_lag4'] = data_monthly['chg_oil_spot_WTI_Positive'].shift(4)
data_monthly['chg_oil_spot_WTI_Positive_lag5'] = data_monthly['chg_oil_spot_WTI_Positive'].shift(5)
data_monthly['chg_oil_spot_WTI_Positive_lag6'] = data_monthly['chg_oil_spot_WTI_Positive'].shift(6)


data_monthly['chg_oil_spot_WTI_Negative_lag1'] = data_monthly['chg_oil_spot_WTI_Negative'].shift(1)
data_monthly['chg_oil_spot_WTI_Negative_lag2'] = data_monthly['chg_oil_spot_WTI_Negative'].shift(2)
data_monthly['chg_oil_spot_WTI_Negative_lag3'] = data_monthly['chg_oil_spot_WTI_Negative'].shift(3)
data_monthly['chg_oil_spot_WTI_Negative_lag4'] = data_monthly['chg_oil_spot_WTI_Negative'].shift(4)
data_monthly['chg_oil_spot_WTI_Negative_lag5'] = data_monthly['chg_oil_spot_WTI_Negative'].shift(5)
data_monthly['chg_oil_spot_WTI_Negative_lag6'] = data_monthly['chg_oil_spot_WTI_Negative'].shift(6)



data_monthly['chg_oil_spot_WTI_lag1'] = data_monthly['chg_oil_spot_WTI'].shift(1)
data_monthly['chg_oil_spot_WTI_lag2'] = data_monthly['chg_oil_spot_WTI'].shift(2)
data_monthly['chg_oil_spot_WTI_lag3'] = data_monthly['chg_oil_spot_WTI'].shift(3)
data_monthly['chg_oil_spot_WTI_lag4'] = data_monthly['chg_oil_spot_WTI'].shift(4)
data_monthly['chg_oil_spot_WTI_lag5'] = data_monthly['chg_oil_spot_WTI'].shift(5)
data_monthly['chg_oil_spot_WTI_lag6'] = data_monthly['chg_oil_spot_WTI'].shift(6)



data_monthly['future_oil_contract_1_lag1'] = data_monthly['future_oil_contract_1'].shift(1)
data_monthly['future_oil_contract_1_lag2'] = data_monthly['future_oil_contract_1'].shift(2)
data_monthly['future_oil_contract_1_lag3'] = data_monthly['future_oil_contract_1'].shift(3)
data_monthly['future_oil_contract_1_lag4'] = data_monthly['future_oil_contract_1'].shift(4)
data_monthly['future_oil_contract_1_lag5'] = data_monthly['future_oil_contract_1'].shift(5)
data_monthly['future_oil_contract_1_lag6'] = data_monthly['future_oil_contract_1'].shift(6)




data_monthly['oil_spot_WTI_Positive'] = np.where(data_monthly['oil_spot_WTI'] >= data_monthly['oil_spot_WTI'].shift(1) ,data_monthly['oil_spot_WTI'] ,0)
data_monthly['oil_spot_WTI_Negative'] = np.where(data_monthly['oil_spot_WTI'] < data_monthly['oil_spot_WTI'].shift(1) ,data_monthly['oil_spot_WTI'] ,0)



data_monthly['oil_spot_WTI_Positive_lag1'] = data_monthly['oil_spot_WTI_Positive'].shift(1)
data_monthly['oil_spot_WTI_Positive_lag2'] = data_monthly['oil_spot_WTI_Positive'].shift(2)
data_monthly['oil_spot_WTI_Positive_lag3'] = data_monthly['oil_spot_WTI_Positive'].shift(3)
data_monthly['oil_spot_WTI_Positive_lag4'] = data_monthly['oil_spot_WTI_Positive'].shift(4)
data_monthly['oil_spot_WTI_Positive_lag5'] = data_monthly['oil_spot_WTI_Positive'].shift(5)
data_monthly['oil_spot_WTI_Positive_lag6'] = data_monthly['oil_spot_WTI_Positive'].shift(6)

data_monthly['oil_spot_WTI_Negative_lag1'] = data_monthly['oil_spot_WTI_Negative'].shift(1)
data_monthly['oil_spot_WTI_Negative_lag2'] = data_monthly['oil_spot_WTI_Negative'].shift(2)
data_monthly['oil_spot_WTI_Negative_lag3'] = data_monthly['oil_spot_WTI_Negative'].shift(3)
data_monthly['oil_spot_WTI_Negative_lag4'] = data_monthly['oil_spot_WTI_Negative'].shift(4)
data_monthly['oil_spot_WTI_Negative_lag5'] = data_monthly['oil_spot_WTI_Negative'].shift(5)
data_monthly['oil_spot_WTI_Negative_lag6'] = data_monthly['oil_spot_WTI_Negative'].shift(6)



data_monthly['future_oil_contract_1_Positive'] = np.where(data_monthly['future_oil_contract_1'] >= data_monthly['future_oil_contract_1'].shift(1) ,data_monthly['future_oil_contract_1'] ,0)
data_monthly['future_oil_contract_1_Negative'] = np.where(data_monthly['future_oil_contract_1'] < data_monthly['future_oil_contract_1'].shift(1) ,data_monthly['future_oil_contract_1'] ,0)


data_monthly['future_oil_contract_1_Positive_lag1'] = data_monthly['future_oil_contract_1_Positive'].shift(1)
data_monthly['future_oil_contract_1_Positive_lag2'] = data_monthly['future_oil_contract_1_Positive'].shift(2)
data_monthly['future_oil_contract_1_Positive_lag3'] = data_monthly['future_oil_contract_1_Positive'].shift(3)
data_monthly['future_oil_contract_1_Positive_lag4'] = data_monthly['future_oil_contract_1_Positive'].shift(4)
data_monthly['future_oil_contract_1_Positive_lag5'] = data_monthly['future_oil_contract_1_Positive'].shift(5)
data_monthly['future_oil_contract_1_Positive_lag6'] = data_monthly['future_oil_contract_1_Positive'].shift(6)

data_monthly['future_oil_contract_1_Negative_lag1'] = data_monthly['future_oil_contract_1_Negative'].shift(1)
data_monthly['future_oil_contract_1_Negative_lag2'] = data_monthly['future_oil_contract_1_Negative'].shift(2)
data_monthly['future_oil_contract_1_Negative_lag3'] = data_monthly['future_oil_contract_1_Negative'].shift(3)
data_monthly['future_oil_contract_1_Negative_lag4'] = data_monthly['future_oil_contract_1_Negative'].shift(4)
data_monthly['future_oil_contract_1_Negative_lag5'] = data_monthly['future_oil_contract_1_Negative'].shift(5)
data_monthly['future_oil_contract_1_Negative_lag6'] = data_monthly['future_oil_contract_1_Negative'].shift(6)





data['oil_spot_WTI_Positive'] = np.where(data['oil_spot_WTI'] >= data['oil_spot_WTI'].shift(1) ,data['oil_spot_WTI'] ,0)
data['oil_spot_WTI_Negative'] = np.where(data['oil_spot_WTI'] < data['oil_spot_WTI'].shift(1) ,data['oil_spot_WTI'] ,0)









data_monthly = data_monthly.dropna()

