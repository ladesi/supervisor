from django import template
from django.urls import reverse
import requests
from requests.exceptions import HTTPError
from urllib3.exceptions import ConnectionError, NewConnectionError
import math
import json
import numpy as np

register = template.Library()

@register.simple_tag
def get_json(IP_ADDRESS, n):
    if IP_ADDRESS == '127.0.0.1':
        REQUEST_URL = f'http://{IP_ADDRESS}:8000/{reverse("analyser-data")}'
        DEVICE_NAME = 'Modo Teste'
    else:
        REQUEST_URL = f'http://{IP_ADDRESS}'
        DEVICE_NAME = 'ESP-01'

    try:
        r = requests.get(REQUEST_URL)
    except requests.exceptions.RequestException as e:
        REQUEST_URL = f'http://127.0.0.1:8000/{reverse("analyser-data")}'
        DEVICE_NAME = 'IP Inválido - Modo Teste'
        s = requests.get(REQUEST_URL)
        data = s.request.url

    t = requests.get(REQUEST_URL)
    values = json.loads(t.text)
    v = round(21*(values["v"]/0.3125),1)
    i = round(values["i"],2)
    theta = round(values["z"])
    aux = round(values["z"])
    z = round(np.deg2rad(theta),2)

    if (np.sin(z) <= 0):
        theta = round(360 - theta)

    if (theta >= 360):
        theta = round(360 - theta)

    pf = round(np.cos(z),2)
    pa = round(v*i,2)
    pw = round(pa*pf,2)
    pr = round(pa*np.sin(z),2)

    # out_file = '/home/django/Downloads/out.csv'
    # output_csv = f'{v},{i},{theta}\n'

    # with open(out_file, 'at', encoding='utf-8') as f:
    #             f.write(output_csv)

    if n == "v":
        return v
    elif n == "i":
        return i
    elif n == "z":
        return aux
    elif n == "pf":
        return pf
    elif n == "pw":
        return pw
    elif n == "pa":
        return pa
    elif n == "pr":
        return pr
    elif n == "ip":
        return IP_ADDRESS
    elif n == "dev":
        return DEVICE_NAME
    else:
        return values

@register.simple_tag
def get_random(n):
    aux = np.random.uniform(low=0.1, high=0.15, size=(3,))
    v = round(aux[0], 2)
    i = round(10*aux[1], 2)
    z = round(200*aux[2], 2)

    if n == "v":
        return v
    elif n == "i":
        return i
    elif n == "z":
        return z
    else:
        return values
