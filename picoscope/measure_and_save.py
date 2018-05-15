#!/usr/bin/python2

from picosdk import ps3000a as pico
import matplotlib.pyplot as plt
import numpy as np
import sys

if __name__ == "__main__":
    ps = pico.Device()
    status = ps.open_unit()
    if status == ps.m.pico_num("PICO_OK"):
        """configure channels"""
        s, stateA = ps.get_channel_state(channel=ps.m.Channels.A)
        stateA.enabled = True
        stateA.range = ps.m.Ranges.r5v
        s, stateB = ps.get_channel_state(channel=ps.m.Channels.B)
        stateB.enabled = True
        stateB.range = ps.m.Ranges.r200mv
        status = ps.set_channel(channel=ps.m.Channels.A, state=stateA)
        status = ps.set_channel(channel=ps.m.Channels.B, state=stateB)

        ps.set_simple_trigger(True, ps.m.Channels.A, 0.6, ps.m.ThresholdDirections.rising)

        """ config """
        num_runs = 1
        num_traces = 10000
        num_samples = 2000
        path = "run_{:02}.npy"

        if status == ps.m.pico_num("PICO_OK"):
            s, index = ps.locate_buffer(channel=ps.m.Channels.B,
                                        samples=num_samples,
                                        segment=0,
                                        mode=ps.m.RatioModes.raw,
                                        downsample=0)

            for r in range(num_runs):
                all_data = np.zeros((num_traces, num_samples))
                for i in range(num_traces):
                    print("{}/{}".format(i,num_traces))
                    status = ps.collect_segment(segment=0, interval=50)
                    if status == ps.m.pico_num("PICO_OK"):
                        status, all_data[i] = ps.get_buffer_volts(index=index)
                    else:
                        print(ps.m.pico_tag(status))
                        sys.exit(-1)

                np.save(path.format(r), all_data)

    print ps.m.pico_tag(status)
