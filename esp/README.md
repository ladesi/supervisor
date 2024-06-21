# Programação do módulo ESP-01

A programação do módulo é realizada através da IDE do Arduino, disponível em: https://www.arduino.cc/en/software

## Instalação do pacote

- Após a instalação do *software* é necessário adicionar o repositório do pacote referente às placas do módulo `ESP8266`. Acesse **Arquivo > Preferências** e insira `https://arduino.esp8266.com/stable/package_esp8266com_index.json` no campo **URLs Adicionais para Gerenciadores de Placas**.

- Clique em ok.

- Pesquise por `esp8266` em **Ferramentas > Placa > Gerenciador de Placas** e instale o pacote *esp8266*.

## Programação da placa

- Inicialmente, escolha a opção `Generic ESP8266 Module` em **Ferramentas > Placa**.

- Abra o arquivo **main.c**.

- Defina a taxa de transmissão (baudrate) para 9600. Deve ser a mesma definida na programação do PIC.

- Defina as constantes **ssid** e **password** de acordo com suas configurações de rede.

- Clique em **upload**.
