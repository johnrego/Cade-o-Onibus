#!/usr/bin/env python
# -*- coding: utf-8 -*-
import time
from funcao import atualizaOnibus

#ori = '-6.128172,-38.206329'
#lon = '-6.106254,-38.184007'
#lugar = '-6.106254,-38.184007'

'''
i = -1
if(type(i) is int):
	print 'inteiro'
else:
	print 'erro'

'''

while True:
	try:
		atualizaOnibus()
	except KeyboardInterrupt:
		break
print 'Fim'