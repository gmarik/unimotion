all: sub-unimotion sub-motion sub-calibrate

clean:
	$(MAKE) -C unimotion clean
	rm -rf Frameworks
	$(MAKE) -C motion clean
	$(MAKE) -C calibrate clean
	rm -rf bin
	find . -name .DS_Store -exec rm "{}" \;

sub-unimotion:
	$(MAKE) -C unimotion

sub-motion: sub-unimotion
	$(MAKE) -C motion

sub-calibrate: sub-unimotion
	$(MAKE) -C calibrate

