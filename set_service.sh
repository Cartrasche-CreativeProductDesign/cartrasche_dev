#!/bin/sh
sudo chmod +x run_cartrasche.sh
sudo cp cartrasche.service /etc/systemd/system/cartrasche.service
systemctl daemon-reload
systemctl enable cartrasche