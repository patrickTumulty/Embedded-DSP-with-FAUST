import("stdfaust.lib");


oscsin(freq) = rdtable(tablesize, os.sinwaveform(tablesize), int(os.phasor(tablesize,freq)))
with {
	tablesize = 1 << 8;
};

flanger(freq, wet, depth) = _<:de.delay(128, d) * wet ,_ :> _ 
with{
    d = (oscsin(freq) + 1) * 63 * depth; // 0 and 2
};
modFreq = hslider("Fq", 10, 0.5, 100, 0.1);
modWet = hslider("Wet", 0.5, 0.01, 1, 0.01);
modDepth = hslider("Depth", 0.5, 0.1, 1, 0.1);

// process = flanger(modFreq, modWet, modDepth);
process = oscsin(modFreq);

