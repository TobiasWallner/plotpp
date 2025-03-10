#pragma once

#include "optional_ptr.hpp"
#include "plotpp/concepts.hpp"
#include "plotpp/Multiplot.hpp"
#include "plotpp/Line.hpp"

/// @example bode.cpp

namespace plotpp{

	/**
		@brief Creates a bode plotpp
		
		Creates a multiplot with two plots on top of each other. 
		The top one will show the amplitued and the bottom will show the phase over the frequency.
		The freqency axis will be formated to be in log-scale.
		
		@param frequencies : PtrOrMoved - The frequency values as a container with `begin()` and `end()` iterators that is either a pointer (raw or smart) or the moved container itself. 
		@param amplitudes : PtrOrMoved - The amplitudes values as a container with `begin()` and `end()` iterators that is either a pointer (raw or smart) or the moved container itself. 
		@param phases : PtrOrMoved - The phases values as a container with `begin()` and `end()` iterators that is either a pointer (raw or smart) or the moved container itself. 
		
		@param title : std::string - The title of the bode plot - Multiplot (default: "Bode Diagram")
		@param freqLabel : std::string - The label of the frequency-axis (default: "Frequency in Hz")
		@param ampLabel : std::string - The label of the ampLabel-axis (default: "Frequency in Hz")
		@param phaseLabel : std::string - The label of the phaseLabel-axis (default: "Frequency in Hz")
		
		@returns Multiplot - The generated bode plot.
	*/
	template<PtrOrMoved Uf, PtrOrMoved Uamp, PtrOrMoved Uphi>
	Multiplot bode(	Uf&& frequencies, Uamp&& amplitudes, Uphi&& phases, 
					std::string title = "Bode Diagram", 
					std::string freqLabel = "Frequency in Hz", 
					std::string ampLabel = "Amplitude in dB", 
					std::string phaseLabel = "Phase in deg"){
		using Tf = remove_ptr_t<std::remove_reference_t<Uf>>;
		using Tamp = remove_ptr_t<std::remove_reference_t<Uamp>>;
		using Tphi = remove_ptr_t<std::remove_reference_t<Uphi>>;
		
		optional_ptr<Tf> freq(std::forward<Uf>(frequencies));
		optional_ptr<Tf> amp(std::forward<Uf>(amplitudes));
		optional_ptr<Tf> phi(std::forward<Uf>(phases));
		
		const size_t rows = 2;
		const size_t columns = 1;
		Multiplot mplt(rows, columns, title);
		mplt.at(0, 0).add(Line(freq, std::move(amp))).xLabel(freqLabel).yLabel(ampLabel).xLog();
		mplt.at(1, 0).add(Line(std::move(freq), std::move(phi))).xLabel(freqLabel).yLabel(phaseLabel).xLog();
		mplt.grid();
		return mplt;
	}

}