.model flat, c
.data
.code

StressCheat			PROC

	mov		DWORD PTR [esi+0DE4h], 0	;put a 0 before the start or it gives an error

	ret

StressCheat			ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

HealthCheat			PROC

	mov		DWORD PTR [ebp + 0Ch], 0
	subss	xmm0, DWORD PTR [ebp + 0Ch]

	ret

HealthCheat			ENDP

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

EnemyHealthCheat	PROC

	subss	xmm0,xmm1
	xorps	xmm0,xmm0
	movss	DWORD PTR [ebx+0CACh],xmm0
	ret
	

EnemyHealthCheat	ENDP

end