#!/usr/bin/env python
# -*- coding: utf-8 -*-
import json
import serial
import requests

def atualizaOnibus():
	conexao = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
	if conexao:
		for x in range(0,3):
			linha = conexao.readline().replace('\n', '').replace('\r', '').split(';')
			if len(linha)>2:
				if (len(linha[0])>7) and (len(linha[1])>8):
					'''
					f = open('json/onibus.json', 'w')
					f.write(json.dumps(([{'nome': 'onibus',
						'lat': linha[0],
						'lon': linha[1]}]), sort_keys=True, indent=4, separators=(',', ': ')))
					f.close()
					atualizaTrajetoria(linha[0], linha[1])
					'''
					print linha
					break
		conexao.close()

def atualizaTrajetoria(latitude, longitude):
	f = open('json/trajetoria.json', 'r')
	antigo = f.read()
	f.close()
	if len(antigo)>2:
		dados = json.loads(antigo)
		dados.append({'nome': 'Percurso',
						'lat': latitude,
						'lon': longitude})
	else:
		dados = [{'nome': 'Percurso',
					'lat': latitude,
					'lon': longitude}]
	f = open('json/trajetoria.json', 'w')
	f.write(json.dumps(dados, sort_keys=True, indent=4, separators=(',', ': ')))
	f.close()

def distancia(ori, op, rot):
	url = 'https://maps.googleapis.com/maps/api/distancematrix/json?&language=pt-BR&origins=' + ori + '&destinations=' + des + '&key=AIzaSyDT3Y8yZO03B-sAnrolBobK28iMDPDNnbs'
	#ori = '-6.128172,-38.206329'
	des = '-6.106254,-38.184007'
	s = requests.Session()
	resp = s.get(url)
	dados = json.loads(resp.content)
	#print dados.keys()
	if(dados['status']=='OK'):
		if(op==1):
			return len(dados['rows'])
		elif(op==2):
			return dados['rows'][x]['elements'][rot]['distance']['text']
		elif(op==3):
			return dados['rows'][x]['elements'][rot]['distance']['value']
		elif(op==4):
			return dados['rows'][x]['elements'][rot]['duration']['text']
		else:
			return -1
	else:
		return -1

def geocodificacao(lugar):
	url = 'https://maps.googleapis.com/maps/api/geocode/json?latlng=' + lugar + '&key=AIzaSyCkhdzwJk96Q19VrfDHwQYH19KQTFzP7oA'
	#lugar = '-6.106254,-38.184007'
	s = requests.Session()
	resp = s.get(url)
	dados = json.loads(resp.content)
	#print dados.keys()
	if(dados['status']=='OK'):
		return dados['results'][0]['formatted_address']
	else:
		return -1