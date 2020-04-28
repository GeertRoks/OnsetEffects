#ifndef DISTRHO_PLUGIN_SLPLUGIN_HPP_INCLUDED
#define DISTRHO_PLUGIN_SLPLUGIN_HPP_INCLUDED

#include "DistrhoPlugin.hpp"
#include "flanger/flanger.hpp"


START_NAMESPACE_DISTRHO

class FlangerOnsetSyncPlugin : public Plugin
{
	public:
		enum Parameters
		{
            paramRate,
            paramDepth,
            paramFeedback,
            paramPredelay,
			paramCount
		};

		FlangerOnsetSyncPlugin();
		~FlangerOnsetSyncPlugin();

	protected:
		//-------------------------------------------------------------------
		// Information

		const char* getLabel() const noexcept override
		{
			return "FlangerOnsetSyncPlugin";
		}

		const char* getDescription() const override
		{
			return "A guitar flanger that syncs its lfo at the beginning of the guitar note.";
		}

		const char* getMaker() const noexcept override
		{
			return "Geert Roks";
		}

		const char* getHomePage() const override
		{
			return "http://geertroks.com";
		}

		const char* getLicense() const noexcept override
		{
			return "MIT";
		}

		uint32_t getVersion() const noexcept override
		{
			return d_version(1, 0, 0);
		}

		int64_t getUniqueId() const noexcept override
		{
			return d_cconst('F', 'O', 'S', 'P');
		}

		// -------------------------------------------------------------------
		// Init

		void initParameter(uint32_t index, Parameter& parameter) override;
		void initProgramName(uint32_t index, String& programName) override;

		// -------------------------------------------------------------------
		// Internal data

		float getParameterValue(uint32_t index) const override;
		void  setParameterValue(uint32_t index, float value) override;
		void  loadProgram(uint32_t index) override;

		// -------------------------------------------------------------------
		// Process
		void activate() override;
		void deactivate() override;
		void run(const float** inputs, float** outputs, uint32_t frames) override;

	private:
		int bIndex = 0;
		double pSignal = 0.0;

        Flanger flanger;

		void reset();

		DISTRHO_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR(FlangerOnsetSyncPlugin)
};

// -----------------------------------------------------------------------

END_NAMESPACE_DISTRHO

#endif  // DISTRHO_PLUGIN_SLPLUGIN_HPP_INCLUDED

