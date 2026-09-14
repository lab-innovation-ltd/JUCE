/*
  ==============================================================================

   This file is part of the JUCE framework.
   Copyright (c) Raw Material Software Limited

   JUCE is an open source framework subject to commercial or open source
   licensing.

   By downloading, installing, or using the JUCE framework, or combining the
   JUCE framework with any other source code, object code, content or any other
   copyrightable work, you agree to the terms of the JUCE End User Licence
   Agreement, and all incorporated terms including the JUCE Privacy Policy and
   the JUCE Website Terms of Service, as applicable, which will bind you. If you
   do not agree to the terms of these agreements, we will not license the JUCE
   framework to you, and you must discontinue the installation or download
   process and cease use of the JUCE framework.

   JUCE End User Licence Agreement: https://juce.com/legal/juce-8-licence/
   JUCE Privacy Policy: https://juce.com/juce-privacy-policy
   JUCE Website Terms of Service: https://juce.com/juce-website-terms-of-service/

   Or:

   You may also use this code under the terms of the AGPLv3:
   https://www.gnu.org/licenses/agpl-3.0.en.html

   THE JUCE FRAMEWORK IS PROVIDED "AS IS" WITHOUT ANY WARRANTY, AND ALL
   WARRANTIES, WHETHER EXPRESSED OR IMPLIED, INCLUDING WARRANTY OF
   MERCHANTABILITY OR FITNESS FOR A PARTICULAR PURPOSE, ARE DISCLAIMED.

  ==============================================================================
*/

namespace juce
{

/**
    An interface to allow an AudioProcessor to receive Audio Unit specific host
    information that the stock wrapper has no channel for.

    To use this class, create an object that inherits from it, implement the methods,
    then return a pointer to the object in your AudioProcessor::getAudioUnitClientExtensions()
    method.

    @see AudioProcessor, VST3ClientExtensions

    @tags{Audio}
*/
struct AudioUnitClientExtensions
{
    virtual ~AudioUnitClientExtensions() = default;

    /** Called by the AU wrapper when the host writes kAudioUnitProperty_PresentationLatency.

        The host declares, per scope and element (bus), how long audio takes to reach the
        listener after leaving that bus: the whole downstream chain including any latency
        compensation the host applies. Logic Pro writes the output-scope value whenever a
        look-ahead plug-in downstream changes it.

        This may be called from the host's UI thread, before or after prepareToPlay(), and
        may not be called at all. The wrapper reports the property as supported and writable
        regardless of whether an extensions object is returned.

        @param scope     the AudioUnitScope the host wrote (kAudioUnitScope_Output is 2)
        @param element   the bus index within that scope
        @param seconds   the declared latency in seconds
    */
    virtual void presentationLatencyChanged (unsigned int scope, unsigned int element, double seconds) = 0;
};

} // namespace juce
