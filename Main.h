void CmdStart(const edict_t *player, const struct usercmd_s *cmd, unsigned int random_seed);
class Key{
	public:
		Key(){
			isActive = true;
		}
		~Key(){
			if(fwdId!=-1)MF_UnregisterSPForward(fwdId);
		}
		bool isActive;
		int fwdId, KeysBitSum;
};
extern DLL_FUNCTIONS *g_pFunctionTable;