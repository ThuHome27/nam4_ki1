#select TenNCC from ncc, cungcap, mathang
#where ncc.MSNCC = cungcap.MSNCC and cungcap.MSMH = mathang.MSMH
#		and mathang.mausac = 'do'

#b
#select MSNCC from cungcap, mathang
#where and cungcap.MSMH = mathang.MSMH
#		and mathang.mausac in ('do', 'xanh')

#c
#select MSNCC from cungcap, mathang
#where cungcap.MSMH = mathang.MSMH and mathang.mausac = 'xanh'
#	and cungcap.MSNCC in (select MSNCC from cungcap, mathang
#						where cungcap.MSMH = mathang.MSMH
#						and mathang.mausac = 'do')
                        
#d
#select MSNCC from cungcap, mathang
#where cungcap.MSMH = mathang.MSMH and mathang.mausac = 'do'
#group by MSNCC 
#having count(cungcap.MSMH) = (select count(mathang.MSMH) from mathang
#						where mathang.mausac = 'do')
                        
#e
#select MSNCC from cungcap, mathang
#where MSNCC in (select MSNCC from cungcap, mathang
#				where cungcap.MSMH = mathang.MSMH and mathang.mausac = 'do'
#				group by MSNCC 
#				having count(cungcap.MSMH) = (select count(mathang.MSMH) from mathang
#						where mathang.mausac = 'do')
#				)
 #    and cungcap.MSMH = mathang.MSMH and mathang.mausac = 'xanh'
#group by MSNCC 
#having count(cungcap.MSMH) = (select count(mathang.MSMH) from mathang
#						where mathang.mausac = 'xanh')

#f
#select distinct MSNCC from cungcap, mathang
#where MSNCC in (select MSNCC from cungcap, mathang
#				where cungcap.MSMH = mathang.MSMH and mathang.mausac = 'do'
#				group by MSNCC 
#				having count(cungcap.MSMH) = (select count(mathang.MSMH) from mathang
#						where mathang.mausac = 'do')
#				)
#	or MSNCC in (select MSNCC from cungcap, mathang
#				where cungcap.MSMH = mathang.MSMH and mathang.mausac = 'xanh'
#				group by MSNCC 
#				having count(cungcap.MSMH) = (select count(mathang.MSMH) from mathang
#						where mathang.mausac = 'xanh')
#				)

#h
#select MSMH from cungcap
#group by MSMH
#having count(MSNCC) > 1

#i
#select MSMH from cungcap, ncc
#where giatien = (select max(giatien) from cungcap, ncc
#						where cungcap.MSNCC = ncc.MSNCC and ncc.TenNCC = 'dustin')
#	and cungcap.MSNCC = ncc.MSNCC and ncc.TenNCC = 'dustin'

#j
#select MSMH from cungcap
#where giatien < 200
#group by MSMH 
#having count(MSNCC) = (select count(MSNCC) from ncc)



