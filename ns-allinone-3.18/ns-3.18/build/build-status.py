#! /usr/bin/env python

# Programs that are runnable.
ns3_runnable_programs = ['build/src/adtcp/examples/ns3.18-adtcp-example-debug', 'build/src/aodv/examples/ns3.18-aodv-debug', 'build/src/bridge/examples/ns3.18-csma-bridge-debug', 'build/src/bridge/examples/ns3.18-csma-bridge-one-hop-debug', 'build/src/buildings/examples/ns3.18-buildings-pathloss-profiler-debug', 'build/src/config-store/examples/ns3.18-config-store-save-debug', 'build/src/core/examples/ns3.18-main-callback-debug', 'build/src/core/examples/ns3.18-sample-simulator-debug', 'build/src/core/examples/ns3.18-main-ptr-debug', 'build/src/core/examples/ns3.18-main-random-variable-debug', 'build/src/core/examples/ns3.18-main-random-variable-stream-debug', 'build/src/core/examples/ns3.18-sample-random-variable-debug', 'build/src/core/examples/ns3.18-sample-random-variable-stream-debug', 'build/src/core/examples/ns3.18-command-line-example-debug', 'build/src/core/examples/ns3.18-hash-example-debug', 'build/src/core/examples/ns3.18-main-test-sync-debug', 'build/src/csma/examples/ns3.18-csma-one-subnet-debug', 'build/src/csma/examples/ns3.18-csma-broadcast-debug', 'build/src/csma/examples/ns3.18-csma-packet-socket-debug', 'build/src/csma/examples/ns3.18-csma-multicast-debug', 'build/src/csma/examples/ns3.18-csma-raw-ip-socket-debug', 'build/src/csma/examples/ns3.18-csma-ping-debug', 'build/src/csma-layout/examples/ns3.18-csma-star-debug', 'build/src/dsdv/examples/ns3.18-dsdv-manet-debug', 'build/src/dsr/examples/ns3.18-dsr-debug', 'build/src/emu/examples/ns3.18-emu-udp-echo-debug', 'build/src/emu/examples/ns3.18-emu-ping-debug', 'build/src/energy/examples/ns3.18-li-ion-energy-source-debug', 'build/src/fd-net-device/examples/ns3.18-dummy-network-debug', 'build/src/fd-net-device/examples/ns3.18-fd2fd-onoff-debug', 'build/src/fd-net-device/examples/ns3.18-realtime-dummy-network-debug', 'build/src/fd-net-device/examples/ns3.18-realtime-fd2fd-onoff-debug', 'build/src/fd-net-device/examples/ns3.18-fd-emu-ping-debug', 'build/src/fd-net-device/examples/ns3.18-fd-emu-udp-echo-debug', 'build/src/fd-net-device/examples/ns3.18-fd-emu-onoff-debug', 'build/src/fd-net-device/examples/ns3.18-fd-tap-ping-debug', 'build/src/fd-net-device/examples/ns3.18-fd-tap-ping6-debug', 'build/src/internet/examples/ns3.18-main-simple-debug', 'build/src/lte/examples/ns3.18-lena-cqi-threshold-debug', 'build/src/lte/examples/ns3.18-lena-dual-stripe-debug', 'build/src/lte/examples/ns3.18-lena-fading-debug', 'build/src/lte/examples/ns3.18-lena-intercell-interference-debug', 'build/src/lte/examples/ns3.18-lena-pathloss-traces-debug', 'build/src/lte/examples/ns3.18-lena-profiling-debug', 'build/src/lte/examples/ns3.18-lena-rem-debug', 'build/src/lte/examples/ns3.18-lena-rem-sector-antenna-debug', 'build/src/lte/examples/ns3.18-lena-rlc-traces-debug', 'build/src/lte/examples/ns3.18-lena-simple-debug', 'build/src/lte/examples/ns3.18-lena-simple-epc-debug', 'build/src/lte/examples/ns3.18-lena-x2-handover-debug', 'build/src/lte/examples/ns3.18-lena-x2-handover-measures-debug', 'build/src/mesh/examples/ns3.18-mesh-debug', 'build/src/mobility/examples/ns3.18-main-grid-topology-debug', 'build/src/mobility/examples/ns3.18-main-random-topology-debug', 'build/src/mobility/examples/ns3.18-main-random-walk-debug', 'build/src/mobility/examples/ns3.18-mobility-trace-example-debug', 'build/src/mobility/examples/ns3.18-ns2-mobility-trace-debug', 'build/src/mobility/examples/ns3.18-bonnmotion-ns2-example-debug', 'build/src/mpi/examples/ns3.18-simple-distributed-debug', 'build/src/mpi/examples/ns3.18-third-distributed-debug', 'build/src/mpi/examples/ns3.18-nms-p2p-nix-distributed-debug', 'build/src/netanim/examples/ns3.18-dumbbell-animation-debug', 'build/src/netanim/examples/ns3.18-grid-animation-debug', 'build/src/netanim/examples/ns3.18-star-animation-debug', 'build/src/netanim/examples/ns3.18-wireless-animation-debug', 'build/src/netanim/examples/ns3.18-uan-animation-debug', 'build/src/netanim/examples/ns3.18-dynamic_linknode-debug', 'build/src/network/examples/ns3.18-main-packet-header-debug', 'build/src/network/examples/ns3.18-main-packet-tag-debug', 'build/src/network/examples/ns3.18-red-tests-debug', 'build/src/network/examples/ns3.18-droptail_vs_red-debug', 'build/src/nix-vector-routing/examples/ns3.18-nix-simple-debug', 'build/src/nix-vector-routing/examples/ns3.18-nms-p2p-nix-debug', 'build/src/olsr/examples/ns3.18-simple-point-to-point-olsr-debug', 'build/src/olsr/examples/ns3.18-olsr-hna-debug', 'build/src/point-to-point/examples/ns3.18-main-attribute-value-debug', 'build/src/propagation/examples/ns3.18-main-propagation-loss-debug', 'build/src/propagation/examples/ns3.18-jakes-propagation-model-example-debug', 'build/src/spectrum/examples/ns3.18-adhoc-aloha-ideal-phy-debug', 'build/src/spectrum/examples/ns3.18-adhoc-aloha-ideal-phy-matrix-propagation-loss-model-debug', 'build/src/spectrum/examples/ns3.18-adhoc-aloha-ideal-phy-with-microwave-oven-debug', 'build/src/stats/examples/ns3.18-gnuplot-example-debug', 'build/src/stats/examples/ns3.18-double-probe-example-debug', 'build/src/stats/examples/ns3.18-gnuplot-aggregator-example-debug', 'build/src/stats/examples/ns3.18-gnuplot-helper-example-debug', 'build/src/stats/examples/ns3.18-file-aggregator-example-debug', 'build/src/stats/examples/ns3.18-file-helper-example-debug', 'build/src/tap-bridge/examples/ns3.18-tap-csma-debug', 'build/src/tap-bridge/examples/ns3.18-tap-csma-virtual-machine-debug', 'build/src/tap-bridge/examples/ns3.18-tap-wifi-virtual-machine-debug', 'build/src/tap-bridge/examples/ns3.18-tap-wifi-dumbbell-debug', 'build/src/topology-read/examples/ns3.18-topology-read-debug', 'build/src/uan/examples/ns3.18-uan-cw-example-debug', 'build/src/uan/examples/ns3.18-uan-rc-example-debug', 'build/src/virtual-net-device/examples/ns3.18-virtual-net-device-debug', 'build/src/wifi/examples/ns3.18-wifi-phy-test-debug', 'build/src/wimax/examples/ns3.18-wimax-ipv4-debug', 'build/src/wimax/examples/ns3.18-wimax-multicast-debug', 'build/src/wimax/examples/ns3.18-wimax-simple-debug', 'build/examples/socket/ns3.18-socket-bound-static-routing-debug', 'build/examples/socket/ns3.18-socket-bound-tcp-static-routing-debug', 'build/examples/socket/ns3.18-socket-options-ipv4-debug', 'build/examples/socket/ns3.18-socket-options-ipv6-debug', 'build/examples/naming/ns3.18-object-names-debug', 'build/examples/energy/ns3.18-energy-model-example-debug', 'build/examples/realtime/ns3.18-realtime-udp-echo-debug', 'build/examples/ipv6/ns3.18-icmpv6-redirect-debug', 'build/examples/ipv6/ns3.18-ping6-debug', 'build/examples/ipv6/ns3.18-radvd-debug', 'build/examples/ipv6/ns3.18-radvd-two-prefix-debug', 'build/examples/ipv6/ns3.18-test-ipv6-debug', 'build/examples/ipv6/ns3.18-fragmentation-ipv6-debug', 'build/examples/ipv6/ns3.18-fragmentation-ipv6-two-MTU-debug', 'build/examples/ipv6/ns3.18-loose-routing-ipv6-debug', 'build/examples/error-model/ns3.18-simple-error-model-debug', 'build/examples/tcp/ns3.18-tcp-large-transfer-debug', 'build/examples/tcp/ns3.18-tcp-nsc-lfn-debug', 'build/examples/tcp/ns3.18-tcp-nsc-zoo-debug', 'build/examples/tcp/ns3.18-tcp-star-server-debug', 'build/examples/tcp/ns3.18-star-debug', 'build/examples/tcp/ns3.18-tcp-bulk-send-debug', 'build/examples/tcp/ns3.18-tcp-nsc-comparison-debug', 'build/examples/tcp/ns3.18-tcp-variants-comparison-debug', 'build/examples/routing/ns3.18-dynamic-global-routing-debug', 'build/examples/routing/ns3.18-static-routing-slash32-debug', 'build/examples/routing/ns3.18-global-routing-slash32-debug', 'build/examples/routing/ns3.18-global-injection-slash32-debug', 'build/examples/routing/ns3.18-simple-global-routing-debug', 'build/examples/routing/ns3.18-simple-alternate-routing-debug', 'build/examples/routing/ns3.18-mixed-global-routing-debug', 'build/examples/routing/ns3.18-simple-routing-ping6-debug', 'build/examples/routing/ns3.18-manet-routing-compare-debug', 'build/examples/stats/ns3.18-wifi-example-sim-debug', 'build/examples/udp-client-server/ns3.18-udp-client-server-debug', 'build/examples/udp-client-server/ns3.18-udp-trace-client-server-debug', 'build/examples/tutorial/ns3.18-hello-simulator-debug', 'build/examples/tutorial/ns3.18-first-debug', 'build/examples/tutorial/ns3.18-second-debug', 'build/examples/tutorial/ns3.18-third-debug', 'build/examples/tutorial/ns3.18-fourth-debug', 'build/examples/tutorial/ns3.18-fifth-debug', 'build/examples/tutorial/ns3.18-sixth-debug', 'build/examples/tutorial/ns3.18-seventh-debug', 'build/examples/wireless/ns3.18-mixed-wireless-debug', 'build/examples/wireless/ns3.18-wifi-adhoc-debug', 'build/examples/wireless/ns3.18-wifi-clear-channel-cmu-debug', 'build/examples/wireless/ns3.18-wifi-ap-debug', 'build/examples/wireless/ns3.18-wifi-wired-bridging-debug', 'build/examples/wireless/ns3.18-simple-wifi-frame-aggregation-debug', 'build/examples/wireless/ns3.18-multirate-debug', 'build/examples/wireless/ns3.18-wifi-simple-adhoc-debug', 'build/examples/wireless/ns3.18-wifi-simple-adhoc-grid-debug', 'build/examples/wireless/ns3.18-wifi-simple-infra-debug', 'build/examples/wireless/ns3.18-wifi-simple-interference-debug', 'build/examples/wireless/ns3.18-wifi-blockack-debug', 'build/examples/wireless/ns3.18-ofdm-validation-debug', 'build/examples/wireless/ns3.18-wifi-hidden-terminal-debug', 'build/examples/wireless/ns3.18-ht-wifi-network-debug', 'build/examples/matrix-topology/ns3.18-matrix-topology-debug', 'build/examples/udp/ns3.18-udp-echo-debug', 'build/scratch/ns3.18-scratch-simulator-debug', 'build/scratch/ns3.18-my-tcp-large-transfer-debug', 'build/scratch/ns3.18-tcp-large-transfer-debug', 'build/scratch/ns3.18-myfirst-debug', 'build/scratch/subdir/ns3.18-subdir-debug', 'build/scratch/ns3.18-myfifth-debug']

# Scripts that are runnable.
ns3_runnable_scripts = ['csma-bridge.py', 'sample-simulator.py', 'wifi-olsr-flowmon.py', 'tap-csma-virtual-machine.py', 'tap-wifi-virtual-machine.py', 'realtime-udp-echo.py', 'simple-routing-ping6.py', 'first.py', 'mixed-wireless.py', 'wifi-ap.py']

