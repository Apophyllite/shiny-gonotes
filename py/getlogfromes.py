#!/usr/local/bin//python
#-*-coding:UTF-8 -*-
import json
import time
import datetime
import commands
import requests
import io
import sys
import json
def loadLog(qtype, csuid=""):
	now_day = datetime.datetime.now()
	Days = datetime.timedelta(days=1)
	dateT = (now_day).strftime("%Y-%m-%d")
	dateF = (now_day - Days).strftime("%Y-%m-%d")
	#print "dataf",dateF,"datat",dateT
	url = 'http://10.10.124.252:9200/mj_log_md_api_%s/_search'%("online")
	header = {'content-type': 'application/json'}
	data = {#"_source": ["qid","resp"],\
				'size':100,\
			"query": {"bool":{\
				"filter":[\
				{"term": {"type": qtype}},\
				{"term" :{"csuid":csuid}},\
				{"range":{"t":{"gte":dateF+'T00:00:00' , "lte": dateT+'T00:00:00'}}}\
				]\
			}}}
	resp = requests.post(url, data=json.dumps(data), headers=header)
	resp = json.loads(resp.text)
	return resp
print loadLog("api11006", "iay5c3efa16b1b0a283708198")
#iay5c3efa16b1b0a283708198
#print loadLog("api11006")
