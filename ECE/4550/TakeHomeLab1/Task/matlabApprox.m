%Take Home Lab 1
%ECE 4550
%Nelson Raphael
% MATLAB Code for Take Home Lab 1


function matlabApprox()

%Using forward Euler

for h = [];

	t = 0:h:
	x = zeros(1,length(t));

	for n = 1:length(t) -1
		% x(n+1) = x(n)+h*(-x(n)+1); Replace this with the equation
		% Representing the pendulum
	end

	plot(t,x)

end

legend('exact','h=2','etc.')
xlabel('t'), ylabel('x')



end
