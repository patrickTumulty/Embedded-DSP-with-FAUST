import("stdfaust.lib");

transpose1(w, x, s, sig) = de.fdelay(maxDelay,d,sig)*ma.fmin(d/x,1) +
	de.fdelay(maxDelay,d+w,sig)*(1-ma.fmin(d/x,1))
with {
	maxDelay = 1024; // 65536
	i = 1 - pow(2, s/12);
	d = i : (+ : +(w) : fmod(_,w)) ~ _;
};  // From : FAUST GitHub 

upperVox1 = hslider("UV1", 0, 0, 12, 1);
upperVox2 = hslider("UV2", 12, 12, 24, 1);
lowerVox = hslider("LV", 0, 0, -12, 1);
wetDry = hslider("Wet/Dry", 0.5, 0.01, 0.99, 0.01);

window = 1000;
crossfade = 48;

wetVoices = (wetDry - 1) / 3;

voice(0) = transpose1(window, crossfade, upperVox1);
voice(1) = transpose1(window, crossfade, upperVox2);
voice(2) = transpose1(window, crossfade, lowerVox);

process =  _ <:_ * wetDry, par(i, 3, voice(i) * wetVoices) :> _;

