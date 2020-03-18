#!/usr/bin/env python
# coding: utf-8

# In[2]:


# imports
import pandas as pd
import numpy as np
import matplotlib.pyplot as plt
import sklearn.ensemble as es
import lightgbm as lgb
import xgboost as xgb

from lightgbm import LGBMRegressor
from xgboost import XGBRegressor
from sklearn.model_selection import train_test_split


# In[3]:


# import datas

# Two original frame : train, test
train = pd.read_csv('./train.csv',low_memory=False)
test = pd.read_csv('./test.csv')

#Data cleaning "birth", "disbursal_date", "score_description"
train.drop("birth", axis=1,inplace=True)
train.drop("disbursal_date", axis=1,inplace=True)
train.drop("score_description", axis=1,inplace=True)
test.drop("birth", axis=1,inplace=True)
test.drop("disbursal_date", axis=1,inplace=True)


# In[4]:


#Copy datas
df_train = train.copy()
df_test = test.copy()
df_train.drop("id", axis=1,inplace=True)
df_test.drop("id", axis=1,inplace=True)


# In[5]:


#Save Feature List and Dividing Categorical Value, Num values
feature_list = [name for name in df_train.columns if name !='score']
feature_list_test = [name for name in df_test.columns if name !='score']
categorical_variables = df_train.columns[(df_train.dtypes =='object') & (df_train.columns != 'score')]
categorical_variables_test = df_test.columns[(df_test.dtypes =='object') & (df_test.columns != 'score')]
num_variables = [name for name in feature_list if name not in categorical_variables]
num_variables_test = [name for name in feature_list_test if name not in categorical_variables_test]


# In[6]:


#Type Change uint8 -> int32
w = df_train[num_variables].values
ww = w.astype('int32')
v = df_test[num_variables_test].values
vv = v.astype('int32')


# In[7]:


#One hot encoding - rookie or student
df_X_onehot = pd.get_dummies(df_train[categorical_variables], prefix_sep='_')
df_X_test_onehot = pd.get_dummies(df_test[categorical_variables_test], prefix_sep='_')


# In[8]:


#Transform dataframe to numpy
X = np.c_[ww, df_X_onehot.values]
y = df_train['score'].values.ravel()
X_test = np.c_[vv, df_X_test_onehot.values]


# In[9]:


#Saving all feature names
feature_names = num_variables + df_X_onehot.columns.tolist()
feature_names_test = num_variables + df_X_test_onehot.columns.tolist()


# In[10]:


#Data Split
Xtrain,Xtest,Ytrain,Ytest = train_test_split(X,y,random_state = 42)
Xtrain.shape, Ytrain.shape, X_test.shape


# In[10]:


# ###### MODEL SELECTION
clf = es.RandomForestRegressor(n_estimators=300, oob_score=True, random_state = 84)
clf.verbose = True
clf.n_jobs = -1
clf


# In[11]:


# #########Acuuracy RandomForest
clf.fit(Xtrain,Ytrain)
print ("Training Score :" + str(clf.score(Xtrain,Ytrain)))
print ("Test Score : " + str(clf.score(Xtest,Ytest)) )


# In[12]:


#Out Of Bagging Score
print('oob score :', clf.oob_score_)


# In[13]:


# ##### PREDICTION
print('Starting predicting...')
Yresult = clf.predict(X_test)


# In[11]:


#Test Data type Processing
X_test_id = X_test[:, [0]]
X_test_id = X_test_id.ravel()
#X_test_id.shape, Yresult.shape


# In[ ]:


#Saving output
pd.DataFrame({'id': X_test_id, 'target' : Yresult.astype('int32')}).to_csv('c:/csv/RandomForest_test.csv', index = False)


# In[15]:


# #########RMSE RandomForest
from sklearn.metrics import mean_squared_error
y_pred = clf.predict(Xtest)
print('The rmse of prediction is:', mean_squared_error(Ytest, y_pred) ** 0.5)


# In[12]:


model = XGBRegressor(
    max_depth=8,
    n_estimators=1000,
    min_child_weight=300, 
    colsample_bytree=0.8, 
    subsample=0.8, 
    eta=0.3,    
    seed=42)

model.fit(
    Xtrain, 
    Ytrain, 
    eval_metric="rmse", 
    eval_set=[(Xtrain, Ytrain), (Xtest, Ytest)], 
    verbose=True, 
    early_stopping_rounds = 10)


# In[ ]:


Y_test = model.predict(X_test)


# In[ ]:


pd.DataFrame({'id': X_test_id, 'target' : Y_test}).to_csv('c:/csv/XGBoost_test.csv', index = False)


# In[13]:


model = LGBMRegressor(boosting_type='gbdt', 
        num_leaves=31, 
        max_depth=-1, 
        learning_rate=0.05, 
        n_estimators=1000, 
        max_bin=255, 
        subsample_for_bin=50000, 
        objective=None, 
        min_split_gain=0, 
        min_child_weight=3,
        min_child_samples=10, 
        subsample=1, 
        subsample_freq=1, 
        colsample_bytree=1, 
        reg_alpha=0.1, 
        reg_lambda=0, 
        seed=42,
        silent=False, 
        early_stopping_rounds = 150,
        nthread=-1)


# In[14]:


#print "trianing the model"
model.fit(Xtrain, Ytrain, 
        eval_metric='rmse',
        eval_set=[(Xtest, Ytest)],
        verbose = True)


# In[ ]:


Y_test = model.predict(X_test)
pd.DataFrame({'id': X_test_id, 'target' : Y_test}).to_csv('c:/csv/LGBM_Regressor_test.csv', index = False)

