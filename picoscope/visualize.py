#!/usr/bin/python2

from picosdk import ps3000a as pico
import matplotlib.pyplot as plt
import numpy as np

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
        num_runs = 300
        num_samples = 100
        samples_start = 0
        samples_end = 100

        if status == ps.m.pico_num("PICO_OK"):
            s, index = ps.locate_buffer(channel=ps.m.Channels.B,
                                        samples=num_samples,
                                        segment=0,
                                        mode=ps.m.RatioModes.raw,
                                        downsample=0)

            all_data = np.zeros((num_runs, num_samples))
            for i in range(num_runs):
                print("{}/{}".format(i,num_runs))
                status = ps.collect_segment(segment=0, interval=25)
                if status == ps.m.pico_num("PICO_OK"):
                    status, all_data[i] = ps.get_buffer_volts(index=index)

            evens = all_data[::2, samples_start:samples_end]
            even_mean = np.mean(evens, axis=0)
            odds = all_data[1::2, samples_start:samples_end]
            odd_mean = np.mean(odds, axis=0)



            plt.figure()
            plt.subplot(211)
            plt.plot(even_mean)
            plt.plot(odd_mean)
            plt.title("means")

            plt.subplot(212)
            plt.plot(even_mean - odd_mean)
            plt.title("diff")

            plt.show()
    print ps.m.pico_tag(status)
