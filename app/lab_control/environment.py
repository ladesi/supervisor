# environment.py
import os
import math
import calendar

# Change point to comma and set two decimals
@register.simple_tag
def env_str(value):
    str_value = f'{value:.2f}'.replace('.',',')
    return str_value

# Main function to refer in settings
def id_environment(**options):
    env = environment(**options)
    env.filters.update({
        'env_str': env_str,
        })
    return env
